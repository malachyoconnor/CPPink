#include "myGUI.h"
#include "myBmpManager.h"
#include <iostream>
#include <system_error>
#include <bitset>

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
    //important, at least 2s
    DEV_Delay_ms(2500);
    std::cout << "Powered down" << std::endl;
    DEV_Module_Exit();
}

vector<UBYTE> Gui::getPixelCopyForScreen() {
    return {&pixels_[0][0], &pixels_[0][0] + (SCREEN_ARRAY_WIDTH * SCREEN_ARRAY_HEIGHT)};
}

void Gui::UpdateScreen() {
    EPD_7IN5_V2_Display(getPixelCopyForScreen().data());
    DEV_Delay_ms(1000);
}

void Gui::UpdatePartOfScreen(Point p1, Point p2) {
    if (not DISPLAY_PARTIAL_ENABLED) {
        EPD_7IN5_V2_Init_Part();
        DISPLAY_PARTIAL_ENABLED = true;
    }

    p1.x = min(p1.x, p2.x);
    p1.y = min(p1.y, p2.y);

    p2.x = max(p1.x, p2.x);
    p2.y = max(p1.y, p2.y);

    EPD_7IN5_V2_Display_Part(getPixelCopyForScreen().data(), p1.x, p1.y, p2.x, p2.y);
}

void Gui::DrawBlackPixel(int x, int y) {
    auto const colByteNumber = x / 8;
    auto const bitNumber = x % 8;
    auto const rowByteNumber = y;

    if (rowByteNumber > SCREEN_ARRAY_HEIGHT || colByteNumber > SCREEN_ARRAY_WIDTH) {
        cout << rowByteNumber << " " << colByteNumber << endl;
        throw std::runtime_error("Invalid screen array index");
    }

    const UBYTE initialByte = pixels_[rowByteNumber][colByteNumber];
    const UBYTE finalByte = initialByte & ~(0x80 >> bitNumber);
    pixels_[rowByteNumber][colByteNumber] = finalByte;
}

std::unique_ptr<Gui> Gui::create() {
    return std::unique_ptr<Gui>(new Gui());
}

Gui &Gui::createGui() {
    static auto singletonPointer = create();
    return *singletonPointer;
}

void Gui::PrintInternalArray() const {
    for (const auto &row: pixels_) {
        for (const auto &col: row) {
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
        int startX=p1.x, startY=p1.y, endX=p2.x;
        if (p1.x > p2.x) {
            std::swap(startX, endX);
            startY = p2.y;
        }

        double currY = startY;
        for (int x = startX; x <= endX; x++) {
            DrawBlackPixel(x, static_cast<int>(currY));

            const double perfectY = M * x + C;
            while (abs(perfectY - currY) >= 1 - numeric_limits<double>::epsilon()) {
                if (perfectY - currY > 0) {
                    currY += 1;
                } else {
                    currY -= 1;
                }
                DrawBlackPixel(x, static_cast<int>(currY));
            }
        }
    } else {
        int startX=p1.x, startY=p1.y, endY=p2.y;
        if (p1.y > p2.y) {
            std::swap(startY, endY);
            startX = p2.x;
        }

        double currX = startX;
        for (int y = startY; y <= endY; y++) {
            DrawBlackPixel(static_cast<int>(currX), y);

            const double perfectX = (y - C) / M;
            while (abs(perfectX - currX) >= 1 - numeric_limits<double>::epsilon()) {
                if (perfectX - currX >= 0) {
                    currX += 1;
                } else {
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

void Gui::DrawBMP(BmpImage &image) {
    cout << image.data.size() << endl;
    UpdateScreen();
}

void Gui::Sleep(const int millis) {
    DEV_Delay_ms(millis);
}

void Gui::SaveScreenToBmp() const {
    BmpImage pixelBmpImage = CreateBMP(pixels_);
    SaveBMP("test.bmp", pixelBmpImage);
}
