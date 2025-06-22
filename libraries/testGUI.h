#ifndef MYGUI_H
#define MYGUI_H

#include <array>
#include <memory>
#include <thread>
#include <vector>

#include "baseGUI.h"
#include "point.h"
#include "bounding_box.h"

const BoundaryBox SCREEN_BOUNDS = {
    {0, 0},
    {EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT}
};

class TestGui : public BaseGUI {
    friend struct std::default_delete<TestGui>;
    friend struct std::unique_ptr<TestGui>;

protected:
    static std::unique_ptr<TestGui> create();

private:
    TestGui();
    std::array<std::array<UBYTE, EPD_7IN5_V2_WIDTH>, EPD_7IN5_V2_HEIGHT> pixels_{};
    std::mutex pixels_lock{};

    BoundaryBox DrawChar(char toDraw, Point bottomLeft);

    void raylibScreenManager();
    std::thread screen_thread;
    std::atomic_bool screen_changed = false;

public:
    ~TestGui();

    static TestGui& createGui();

    TestGui(const TestGui&) = delete;

    TestGui& operator=(const TestGui&) = delete;

    void UpdateScreen();

    void PrintInternalArray() const;

    // void UpdatePartOfScreen(Point bottomLeft, Point topRight);

    void DrawBlackPixel(int x, int y);

    void DrawLine(Point p1, Point p2);

    void DrawLineWithoutUpdating(Point p1, Point p2);

    void DrawRectangle(Point topLeft, Point bottomRight);

    void DrawRectangleWithoutUpdating(Point p1, Point p2);

    void DrawBMP(BmpImage& image);

    BoundaryBox DrawText_(string stringToDraw, Point bottomLeftBoundary);

    void Sleep(int millis);

    void SaveScreenToBmp(filesystem::path& path) const;
};

#endif  // MYGUI_H
