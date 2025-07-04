#ifndef MYGUI_H
#define MYGUI_H

#include <array>
#include <memory>
#include <vector>

#include "../utils/BaseScreenController.h"
#include "../utils/bmpManager.h"
#include "Point.h"
#include "BoundaryBox.h"

// Each bit is a pixel.
using PIXEL_ARRAY =
std::array<std::array<UBYTE, SCREEN_ARRAY_WIDTH>, SCREEN_ARRAY_HEIGHT>;
constexpr int TOTAL_SCREEN_BYTES = SCREEN_ARRAY_WIDTH * SCREEN_ARRAY_HEIGHT;
const BoundaryBox SCREEN_BOUNDS = {
   {0, 0},
   {EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT}
};

class ScreenController : public BaseScreenController {
   friend struct std::default_delete<ScreenController>;
   friend struct std::unique_ptr<ScreenController>;

protected:
   static std::unique_ptr<ScreenController> create();

private:
   ScreenController();

   PIXEL_ARRAY pixels_{};

   std::vector<UBYTE> getPixelCopyForScreen();

   bool DISPLAY_PARTIAL_ENABLED = false;

   BoundaryBox DrawChar(char toDraw, Point bottomLeft);

public:
   ~ScreenController();

   static ScreenController& createGui();

   ScreenController(const ScreenController&) = delete;

   ScreenController& operator=(const ScreenController&) = delete;

   void UpdateScreen();

   void ClearScreen();

   void PrintInternalArray() const;

   // void UpdatePartOfScreen(Point bottomLeft, Point topRight);

   void DrawBlackPixel(int x, int y);

   void DrawLine(Point p1, Point p2);

   void DrawLineWithoutUpdating(Point p1, Point p2);

   void DrawRectangle(Point topLeft, Point bottomRight);

   void DrawRectangleWithoutUpdating(Point p1, Point p2);

   void DrawBMP(BmpImage& image);

   BoundaryBox DrawText_(std::string stringToDraw, Point bottomLeftBoundary);

   void Sleep(int millis);

   void SaveScreenToBmp(std::filesystem::path& path) const;
};

#endif  // MYGUI_H
