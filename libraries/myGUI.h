#ifndef MYGUI_H
#define MYGUI_H
#include <array>
#include <vector>
#include <memory>
#include <myBmpManager.h>
#include <point.h>

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
    PIXEL_ARRAY pixels_{};
    std::vector<UBYTE> getPixelCopyForScreen();
    bool DISPLAY_PARTIAL_ENABLED = false;
    // TODO: Do I need to be storing if I'm in partial update mode

public:
    ~Gui();
    static Gui& createGui();
    Gui(const Gui&) = delete;
    Gui& operator=(const Gui&) = delete;

    void UpdateScreen();
    void PrintInternalArray() const;
    void UpdatePartOfScreen(Point p1, Point p2);

    void DrawBlackPixel(int x, int y);
    void DrawLine(Point p1, Point p2);
    void DrawLineWithoutUpdating(Point p1, Point p2);
    void DrawRectangle(Point topLeft, Point bottomRight);
    void DrawRectangleWithoutUpdating(Point p1, Point p2);
    void DrawBMP(BmpImage& image);

    void Sleep(int millis);
    void SaveScreenToBmp() const;
};

#endif //MYGUI_H