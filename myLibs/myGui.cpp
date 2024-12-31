#include <ImageData.h>

#include "myGUI.h"
#include "myBmpManager.h"
#include <iostream>
#include <system_error>

Gui::Gui() {
    cout << "Initializing GUI" << endl;
    if (DEV_Module_Init() != 0) {
        throw std::system_error(errno, std::system_category());
    }
    EPD_7IN5_V2_Init();
    EPD_7IN5_V2_Clear();
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

UBYTE *Gui::getContiguousStore() {
    return &pixels_[0][0];
}

void Gui::flipPixel(int x, int y) {
    auto const colByteNumber = x / 8;
    auto const bitNumber = x % 8;
    auto const rowByteNumber = y;

    if (rowByteNumber > SCREEN_ARRAY_HEIGHT || colByteNumber > SCREEN_ARRAY_WIDTH) {
        cout << rowByteNumber << " " << colByteNumber << endl;
        throw std::runtime_error("Invalid screen array index");
    }

    auto const initialByte = pixels_[rowByteNumber][colByteNumber];
    auto const finalByte = initialByte | (1 << bitNumber);
    pixels_[rowByteNumber][colByteNumber] = finalByte;
}

std::unique_ptr<Gui> Gui::create() {
    return std::unique_ptr<Gui>(new Gui());
}

Gui &Gui::instance() {
    static auto singletonPointer = create();
    return *singletonPointer;
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
    for (int y = EPD_7IN5_V2_HEIGHT / 2 - 25; y < EPD_7IN5_V2_HEIGHT / 2 + 25; y++) {
        for (int x = 0; x < EPD_7IN5_V2_WIDTH; x++) {
            flipPixel(x, y);
        }
    }

    for (int x = EPD_7IN5_V2_WIDTH / 2 - 25; x < EPD_7IN5_V2_WIDTH / 2 + 25; x++) {
        for (int y = 0; y < EPD_7IN5_V2_HEIGHT - 30; y++) {
            flipPixel(x, y);
        }
    }

    EPD_7IN5_V2_Display(getContiguousStore());
    DEV_Delay_ms(2000);

    UBYTE tmp[100 * 480]{0};
    for (int i = 0; i < 100*480; i++) {
        tmp[i] = gImage_7in5[i];
    }

    EPD_7IN5_V2_Display(tmp);
    DEV_Delay_ms(20000);
    return 0;
}

void Gui::saveBmpFile() const {
    BmpImage pixelBmpImage = CreateBMP(pixels_);
    SaveBMP("test.bmp", pixelBmpImage);
}
