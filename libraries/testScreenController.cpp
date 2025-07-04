#include "testScreenController.h"

#include <format>
#include <numeric>

#include "raylib.h"
#include <thread>

#include "fonts.h"

constexpr int FPS = 60;

std::unique_ptr<TestScreenController> TestScreenController::create() {
   return std::unique_ptr<TestScreenController>(new TestScreenController());
}

TestScreenController::TestScreenController() {
   screen_thread = std::thread(&TestScreenController::raylibScreenManager, this);

   while (!IsWindowReady()) {
   }
}

void TestScreenController::raylibScreenManager() {
   const int width = EPD_7IN5_V2_WIDTH;
   const int height = EPD_7IN5_V2_HEIGHT;
   InitWindow(width, height, "Hello");

   while (!WindowShouldClose()) {
      if (screen_changed.exchange(false)) {
         BeginDrawing();

         for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
               DrawPixel(x, y, pixels_[y][x] == 0 ? WHITE : BLACK);
            }
         }

         EndDrawing();
      }
      Sleep(1000 / FPS);
   }
}


TestScreenController::~TestScreenController() {
   CloseWindow();
}

TestScreenController& TestScreenController::createGui() {
   static auto singletonPointer = create();
   return *singletonPointer;
}

void TestScreenController::UpdateScreen() {
   this->screen_changed.exchange(true);
}

void TestScreenController::ClearScreen() {
   for (auto& arr : pixels_) {
      for (auto& ch : arr) {
         ch = 0;
      }
   }
}

void TestScreenController::PrintInternalArray() const {
}

void TestScreenController::DrawBlackPixel(int x, int y) {
   pixels_[y][x] = 255;
}

void TestScreenController::DrawLine(Point p1, Point p2) {
   // TODO: Do proper line-drawing
   DrawLineWithoutUpdating(p1, p2);
   UpdateScreen();
}

void TestScreenController::DrawLineWithoutUpdating(Point p1, Point p2) {
   auto diff = p2 - p1;

   const auto gcd = std::gcd(diff.x, diff.y);
   diff.x /= gcd;
   diff.y /= gcd;

   DrawBlackPixel(p1.x, p1.y);
   while (SCREEN_BOUNDS.contains(p1 + diff) && p1 <= p2) {
      p1 = p1 + diff;
      DrawBlackPixel(p1.x, p1.y);
   }
}

void TestScreenController::DrawRectangle(Point topLeft, Point bottomRight) {
}

void TestScreenController::DrawRectangleWithoutUpdating(Point p1, Point p2) {
}

void TestScreenController::DrawBMP(BmpImage& image) {
}

BoundaryBox TestScreenController::DrawText_(std::string stringToDraw, Point bottomLeftBoundary) {
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

void TestScreenController::Sleep(int millis) {
   std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void TestScreenController::SaveScreenToBmp(std::filesystem::path& path) const {
}

BoundaryBox TestScreenController::DrawChar(char toDraw, Point bottomLeft) {
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
