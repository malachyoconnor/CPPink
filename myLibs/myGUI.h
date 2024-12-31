#ifndef MYGUI_H
#define MYGUI_H

#include <array>
#include <bitset>
#include <GUI_Paint.h>
#include <memory>
#include <EPD_7in5_V2.h>

// Each bit is a pixel.
constexpr int SCREEN_ARRAY_WIDTH = (EPD_7IN5_V2_WIDTH / 8);
constexpr int SCREEN_ARRAY_HEIGHT = EPD_7IN5_V2_HEIGHT;
typedef std::array<std::array<UBYTE, SCREEN_ARRAY_WIDTH>, SCREEN_ARRAY_HEIGHT> PIXEL_ARRAY;

class Gui {
    friend struct std::default_delete<Gui>;
    friend struct std::unique_ptr<Gui>;

    Gui() {
        if (DEV_Module_Init() != 0) {
            throw std::system_error(errno, std::system_category());
        }
        EPD_7IN5_V2_Init();
        EPD_7IN5_V2_Clear();
    };

    ~Gui() {
        EPD_7IN5_V2_Init();
        EPD_7IN5_V2_Clear();
        EPD_7IN5_V2_Sleep();
        //important, at least 2s
        DEV_Delay_ms(2500);
        std::cout << "Powered down" << std::endl;
        DEV_Module_Exit();
    };

    PIXEL_ARRAY pixels_{};

    UBYTE *getContiguousStore() {
        return &pixels_[0][0];
    }

    void drawBlackPixel(int x, int y) {
        auto const colNumber = y;
        auto const rowNumber = x / 8;
        auto const bitNumber = x % 8;

        auto const initialByte = pixels_[colNumber][rowNumber];

        auto const finalByte = initialByte | (1 << bitNumber);

        pixels_[colNumber][rowNumber] = finalByte;
    }

protected:
    static std::unique_ptr<Gui> create() {
        return std::unique_ptr<Gui>(new Gui());
    }

public:
    static Gui &instance() {
        static auto singletonPointer = create();
        return *singletonPointer;
    }

    Gui(const Gui &) = delete;

    Gui &operator=(const Gui &) = delete;

    int refreshScreen() {
        Paint_NewImage(getContiguousStore(), EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, BLACK);
        DEV_Delay_ms(5000);
        return 0;
    }

    void printInternalArray() const {
        for (const auto &row: pixels_) {
            for (const auto &col: row) {
                std::cout << std::bitset<8>(col) << " ";
            }
            std::cout << std::endl;
        }
    }

    int drawSomeStuff() {
        for (int i = 0; i < 50; ++i) {
            drawBlackPixel(i, i);
        }

        Paint_NewImage(getContiguousStore(), EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, BLACK);
        DEV_Delay_ms(5000);

        return 0;
    }

    void saveBmpFile() {
        CreateBMP();
        return;
    }
};

#endif //MYGUI_H
