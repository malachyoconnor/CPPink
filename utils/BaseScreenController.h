#ifndef BASESCREENCONTROLLER_H
#define BASESCREENCONTROLLER_H

#include "bmpManager.h"
#include "Point.h"

class BaseScreenController {
public:
   virtual ~BaseScreenController() = default;

   // Fundamental
   virtual void PrintInternalArray() const = 0;
   virtual void UpdateScreen() = 0;
   virtual void ClearScreen() = 0;

   // Drawing methods
   virtual void DrawBlackPixel(int x, int y) = 0;
   virtual void DrawLine(Point p1, Point p2) = 0;
   virtual void DrawLineWithoutUpdating(Point p1, Point p2) = 0;
   virtual void DrawRectangle(Point topLeft, Point bottomRight) = 0;
   virtual void DrawRectangleWithoutUpdating(Point p1, Point p2) = 0;
   virtual void DrawBMP(BmpImage& image) = 0;
   virtual BoundaryBox DrawText_(std::string stringToDraw, Point bottomLeftBoundary) = 0;

   // Utils
   virtual void Sleep(int millis) = 0;
   virtual void SaveScreenToBmp(std::filesystem::path& path) const = 0;
};


#endif // BASESCREENCONTROLLER_H
