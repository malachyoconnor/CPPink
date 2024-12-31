#include "myGUI.h"
#include "myBmpManager.h"
#include <iostream>
#include <system_error>

Gui::Gui() {
    if (DEV_Module_Init() != 0) {
        throw std::system_error(errno, std::system_category());
    }
    EPD_7IN5_V2_Init();
    EPD_7IN5_V2_Clear();
}

Gui::~Gui() {
    EPD_7IN5_V2_Init();
    EPD_7IN5_V2_Clear();
    EPD_7IN5_V2_Sleep();
    //important, at least 2s
    DEV_Delay_ms(2500);
    std::cout << "Powered down" << std::endl;
    DEV_Module_Exit();
}

UBYTE *Gui::getContiguousStore() {
    return &pixels_[0][0];
}

void Gui::drawBlackPixel(int x, int y) {
    auto const colNumber = y;
    auto const rowNumber = x / 8;
    auto const bitNumber = x % 8;
    auto const initialByte = pixels_[colNumber][rowNumber];
    auto const finalByte = initialByte | (1 << bitNumber);
    pixels_[colNumber][rowNumber] = finalByte;
}

std::unique_ptr<Gui> Gui::create() {
    return std::unique_ptr<Gui>(new Gui());
}

Gui &Gui::instance() {
    static auto singletonPointer = create();
    return *singletonPointer;
}

int Gui::refreshScreen() {
    Paint_NewImage(getContiguousStore(), EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, BLACK);
    DEV_Delay_ms(5000);
    return 0;
}

void Gui::printInternalArray() const {
    for (const auto &row: pixels_) {
        for (const auto &col: row) {
            std::cout << std::bitset<8>(col) << " ";
        }
        std::cout << std::endl;
    }
}

int Gui::drawSomeStuff() {
    for (int i = 0; i < 50; ++i) {
        drawBlackPixel(i, i);
    }

    Paint_NewImage(getContiguousStore(), EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, WHITE);
    DEV_Delay_ms(1000);
    return 0;
}

void Gui::saveBmpFile() const {
    BmpImage pixelBmpImage = CreateBMP(pixels_);
    SaveBMP("test.bmp", pixelBmpImage);
}
