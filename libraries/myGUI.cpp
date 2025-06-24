#include "myGUI.h"

#include <bitset>
#include <iostream>
#include <system_error>
#include <format>

#include "fonts.h"
#include "myBmpManager.h"

Gui::Gui() {
   cout << "Initializing GUI" << endl;
   if (DEV_Module_Init() != 0) {
      throw std::system_error(errno, std::system_category());
   }
   EPD_7IN5_V2_Init();
   EPD_7IN5_V2_Clear();
   // Fill the screen with white
   fill_n(&pixels_[0][0], SCREEN_ARRAY_WIDTH * SCREEN_ARRAY_HEIGHT, 0xFF);
}

Gui::~Gui() {
   std::cout << "Powering down" << std::endl;
   EPD_7IN5_V2_Init();
   EPD_7IN5_V2_Clear();
   EPD_7IN5_V2_Sleep();
   // important, at least 2s
   DEV_Delay_ms(2500);
   std::cout << "Powered down" << std::endl;
   DEV_Module_Exit();
}

vector<UBYTE> Gui::getPixelCopyForScreen() {
   return {
      &pixels_[0][0],
      &pixels_[0][0] + (SCREEN_ARRAY_WIDTH * SCREEN_ARRAY_HEIGHT)
   };
}

void Gui::UpdateScreen() {
   if (DISPLAY_PARTIAL_ENABLED) {
      EPD_7IN5_V2_Init();
      DISPLAY_PARTIAL_ENABLED = false;
   }

   EPD_7IN5_V2_Display(getPixelCopyForScreen().data());
   DEV_Delay_ms(1000);
}

// TODO: This needs fixing
// void Gui::UpdatePartOfScreen(Point bottomLeft, Point topRight) {
//     if (not DISPLAY_PARTIAL_ENABLED)
//     {
//         EPD_7IN5_V2_Init_Part();
//         DISPLAY_PARTIAL_ENABLED = true;
//     }
//
//     if (not(bottomLeft <= topRight))
//     {
//         throw logic_error("Error: Bounding box for UpdatePartOfScreen invalid.");
//     }
//
//     EPD_7IN5_V2_Display_Part(getPixelCopyForScreen().data(), bottomLeft.x,
//                              topRight.y, topRight.x, bottomLeft.y);
// }

void Gui::DrawBlackPixel(int x, int y) {
   auto const colByteNumber = x / 8;
   auto const bitNumber = x % 8;
   auto const rowByteNumber = y;

   if (rowByteNumber > SCREEN_ARRAY_HEIGHT ||
      colByteNumber > SCREEN_ARRAY_WIDTH) {
      cout << rowByteNumber << " " << colByteNumber << endl;
      throw std::runtime_error("Invalid screen array index");
   }

   const UBYTE initialByte = pixels_[rowByteNumber][colByteNumber];
   const UBYTE finalByte = initialByte & ~(0x80 >> bitNumber);
   pixels_[rowByteNumber][colByteNumber] = finalByte;
}

std::unique_ptr<Gui> Gui::create() { return std::unique_ptr<Gui>(new Gui()); }

Gui& Gui::createGui() {
   static auto singletonPointer = create();
   return *singletonPointer;
}

void Gui::PrintInternalArray() const {
   for (const auto& row : pixels_) {
      for (const auto& col : row) {
         std::cout << std::bitset<8>(col) << " ";
      }
      std::cout << std::endl;
   }
}

void Gui::DrawLineWithoutUpdating(Point p1, Point p2) {
   if (p1.y == p2.y) {
      for (int x = min(p1.x, p2.x); x <= max(p1.x, p2.x); x++) {
         DrawBlackPixel(x, p1.y);
      }
      return;
   }
   if (p1.x == p2.x) {
      for (int y = min(p1.y, p2.y); y <= max(p1.y, p2.y); y++) {
         DrawBlackPixel(p1.x, y);
      }
      return;
   }

   const double M = (static_cast<double>(p2.y) - static_cast<double>(p1.y)) /
      (static_cast<double>(p2.x) - static_cast<double>(p1.x));
   const double C = static_cast<double>(p1.y) - M * static_cast<double>(p1.x);

   int dx = abs(p2.x - p1.x);
   int dy = abs(p2.y - p1.y);

   if (dx > dy) {
      int startX = p1.x, startY = p1.y, endX = p2.x;
      if (p1.x > p2.x) {
         std::swap(startX, endX);
         startY = p2.y;
      }

      double currY = startY;
      for (int x = startX; x <= endX; x++) {
         DrawBlackPixel(x, static_cast<int>(currY));

         const double perfectY = M * x + C;
         while (abs(perfectY - currY) >=
            1 - numeric_limits<double>::epsilon()) {
            if (perfectY - currY > 0) {
               currY += 1;
            }
            else {
               currY -= 1;
            }
            DrawBlackPixel(x, static_cast<int>(currY));
         }
      }
   }
   else {
      int startX = p1.x, startY = p1.y, endY = p2.y;
      if (p1.y > p2.y) {
         std::swap(startY, endY);
         startX = p2.x;
      }

      double currX = startX;
      for (int y = startY; y <= endY; y++) {
         DrawBlackPixel(static_cast<int>(currX), y);

         const double perfectX = (y - C) / M;
         while (abs(perfectX - currX) >=
            1 - numeric_limits<double>::epsilon()) {
            if (perfectX - currX >= 0) {
               currX += 1;
            }
            else {
               currX -= 1;
            }
            DrawBlackPixel(static_cast<int>(currX), y);
         }
      }
   }
}

void Gui::DrawLine(const Point p1, const Point p2) {
   this->DrawLineWithoutUpdating(p1, p2);
   UpdateScreen();
}

void Gui::DrawRectangleWithoutUpdating(Point topLeft, Point bottomRight) {
   topLeft = Point::PointMinimums(topLeft, bottomRight);
   bottomRight = Point::PointMaximums(topLeft, bottomRight);

   auto topRight = Point(bottomRight.x, topLeft.y);
   auto bottomLeft = Point(topLeft.x, bottomRight.y);

   this->DrawLineWithoutUpdating(topLeft, topRight);
   this->DrawLineWithoutUpdating(topRight, bottomRight);
   this->DrawLineWithoutUpdating(bottomRight, bottomLeft);
   this->DrawLineWithoutUpdating(bottomLeft, topLeft);
}

void Gui::DrawRectangle(Point topLeft, Point bottomRight) {
   this->DrawRectangleWithoutUpdating(topLeft, bottomRight);
   this->UpdateScreen();
}

BoundaryBox Gui::DrawChar(char toDraw, Point bottomLeft) {
   if (not SCREEN_BOUNDS.contains(bottomLeft) or
      not SCREEN_BOUNDS.contains(bottomLeft + Point{Font24.Width, 0})) {
      throw std::runtime_error(std::format(
         "Trying to draw a character out of bounds. We tried to draw at {}x{} "
         "for the screen which has a size of {}x{}",
         bottomLeft.x + Font24.Width, bottomLeft.y, SCREEN_BOUNDS.topRight.x,
         SCREEN_BOUNDS.topRight.y));
   }

   auto [fontTable, fontWidth, fontHeight] = Font24;

   Point topLeftBoundary = {bottomLeft.x, bottomLeft.y + fontHeight};
   uint32_t Char_Offset =
      (toDraw - ' ') * fontHeight * (fontWidth / 8 + (fontWidth % 8 ? 1 : 0));

   const unsigned char* ptr = &fontTable[Char_Offset];

   for (UWORD Page = 0; Page < fontHeight; Page++) {
      for (UWORD Column = 0; Column < fontWidth; Column++) {
         if (*ptr & (0x80 >> (Column % 8)))
            this->DrawBlackPixel(topLeftBoundary.x + Column,
                                 topLeftBoundary.y + Page);
         // One pixel is 8 bits
         if (Column % 8 == 7) ptr++;
      } // Write a line
      if (fontWidth % 8 != 0) ptr++;
   }

   return {topLeftBoundary, {bottomLeft.x + fontWidth, bottomLeft.y}};
}

BoundaryBox Gui::DrawText_(string stringToDraw, Point bottomLeftBoundary) {
   Point currentBottomLeft = bottomLeftBoundary;
   for (char charToDraw : stringToDraw) {
      BoundaryBox resultBoundary = DrawChar(charToDraw, currentBottomLeft);
      currentBottomLeft.x = resultBoundary.topRight.x;
   }

   return {
      {bottomLeftBoundary.x, bottomLeftBoundary.y + Font24.Height},
      {
         static_cast<int>(bottomLeftBoundary.x +
            stringToDraw.size() * Font24.Width),
         bottomLeftBoundary.y
      }
   };
}

void Gui::DrawBMP(BmpImage& image) {
   cout << image.data.size() << endl;
   UpdateScreen();
}

void Gui::Sleep(const int millis) { DEV_Delay_ms(millis); }

void Gui::SaveScreenToBmp(filesystem::path& path) const {
   BmpImage pixelBmpImage = CreateBMP(pixels_);
   SaveBMP(path, pixelBmpImage);
}
