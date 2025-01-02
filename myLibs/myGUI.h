#ifndef MYGUI_H
#define MYGUI_H
#include <array>
#include <EPD_7in5_V2.h>
#include <vector>
#include <memory>
#include <GUI_Paint.h>
#include <myBmpManager.h>

// Each bit is a pixel.
using PIXEL_ARRAY = std::array<std::array<UBYTE, SCREEN_ARRAY_WIDTH>, SCREEN_ARRAY_HEIGHT>;
constexpr int TOTAL_SCREEN_BYTES = SCREEN_ARRAY_WIDTH * SCREEN_ARRAY_HEIGHT;

class Gui {
    friend struct std::default_delete<Gui>;
    friend struct std::unique_ptr<Gui>;

protected:
    static std::unique_ptr<Gui> create();

private:
    Gui();
    ~Gui();
    PIXEL_ARRAY pixels_{};
    std::vector<UBYTE> getPixelCopyForScreen();
    void flipPixel(int x, int y);

public:
    static Gui& instance();
    Gui(const Gui&) = delete;
    Gui& operator=(const Gui&) = delete;

    int drawSomeStuff();
    int drawBMP(BmpImage& image);
    void printInternalArray() const;
    void saveScreenToBmp() const;
};

#endif //MYGUI_H