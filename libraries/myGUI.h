#ifndef MYGUI_H
#define MYGUI_H
#include <myBmpManager.h>
#include <point.h>

#include <array>
#include <memory>
#include <vector>

// Each bit is a pixel.
using PIXEL_ARRAY =
    std::array<std::array<UBYTE, SCREEN_ARRAY_WIDTH>, SCREEN_ARRAY_HEIGHT>;
constexpr int TOTAL_SCREEN_BYTES = SCREEN_ARRAY_WIDTH * SCREEN_ARRAY_HEIGHT;
const BoundingBox SCREEN_BOUNDS = {{0, 0},
                                   {EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT}};

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

   BoundingBox DrawChar(char toDraw, Point bottomLeftBoundary);

  public:
   ~Gui();

   static Gui &createGui();

   Gui(const Gui &) = delete;

   Gui &operator=(const Gui &) = delete;

   void UpdateScreen();

   void PrintInternalArray() const;

   void UpdatePartOfScreen(Point p1, Point p2);

   void DrawBlackPixel(int x, int y);

   void DrawLine(Point p1, Point p2);

   void DrawLineWithoutUpdating(Point p1, Point p2);

   void DrawRectangle(Point topLeft, Point bottomRight);

   void DrawRectangleWithoutUpdating(Point p1, Point p2);

   void DrawBMP(BmpImage &image);

   BoundingBox DrawText(string stringToDraw, Point bottomLeftBoundary);

   void Sleep(int millis);

   void SaveScreenToBmp(filesystem::path &path) const;
};

#endif  // MYGUI_H
