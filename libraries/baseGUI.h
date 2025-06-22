#ifndef BASEGUI_H
#define BASEGUI_H
#include "myBmpManager.h"
#include "point.h"

class BaseGUI {
public:
    virtual ~BaseGUI() = default;

    // Fundamental
    virtual void PrintInternalArray() const = 0;
    virtual void UpdateScreen() = 0;

    // Drawing methods
    virtual void DrawBlackPixel(int x, int y) = 0;
    virtual void DrawLine(Point p1, Point p2) = 0;
    virtual void DrawLineWithoutUpdating(Point p1, Point p2) = 0;
    virtual void DrawRectangle(Point topLeft, Point bottomRight) = 0;
    virtual void DrawRectangleWithoutUpdating(Point p1, Point p2) = 0;
    virtual void DrawBMP(BmpImage& image) = 0;
    virtual BoundaryBox DrawText_(string stringToDraw, Point bottomLeftBoundary) = 0;

    // Utils
    virtual void Sleep(int millis) = 0;
    virtual void SaveScreenToBmp(filesystem::path& path) const = 0;
};


#endif //BASEGUI_H
