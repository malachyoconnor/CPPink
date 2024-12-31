#ifndef MYGUI_H
#define MYGUI_H

#include <array>
#include <memory>
#include <GUI_Paint.h>
#include <EPD_7in5_V2.h>

// Each bit is a pixel.
constexpr int SCREEN_ARRAY_WIDTH = (EPD_7IN5_V2_WIDTH / 8);
constexpr int SCREEN_ARRAY_HEIGHT = EPD_7IN5_V2_HEIGHT;
typedef std::array<std::array<UBYTE, SCREEN_ARRAY_WIDTH>, SCREEN_ARRAY_HEIGHT> PIXEL_ARRAY;

class Gui {
    friend struct std::default_delete<Gui>;
    friend struct std::unique_ptr<Gui>;

protected:
    static std::unique_ptr<Gui> create();

private:
    Gui();
    ~Gui();
    PIXEL_ARRAY pixels_{};
    UBYTE* getContiguousStore();
    void flipPixel(int x, int y);

public:
    static Gui& instance();
    Gui(const Gui&) = delete;
    Gui& operator=(const Gui&) = delete;

    int drawSomeStuff();
    void printInternalArray() const;
    void saveBmpFile() const;
};

#endif //MYGUI_H