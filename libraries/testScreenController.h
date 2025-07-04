#ifndef MYGUI_H
#define MYGUI_H

#include <array>
#include <memory>
#include <thread>
#include <vector>

#include "../utils/BaseScreenController.h"
#include "Point.h"
#include "BoundaryBox.h"

const BoundaryBox SCREEN_BOUNDS = {
   {0, 0},
   {EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT}
};

class TestScreenController : public BaseScreenController {
   friend struct std::default_delete<TestScreenController>;
   friend struct std::unique_ptr<TestScreenController>;

protected:
   static std::unique_ptr<TestScreenController> create();

private:
   TestScreenController();
   std::array<std::array<UBYTE, EPD_7IN5_V2_WIDTH>, EPD_7IN5_V2_HEIGHT> pixels_{};
   BoundaryBox DrawChar(char toDraw, Point bottomLeft);

   void raylibScreenManager();
   std::thread screen_thread;
   std::atomic_bool screen_changed = false;

public:
   ~TestScreenController();

   static TestScreenController& createGui();

   TestScreenController(const TestScreenController&) = delete;

   TestScreenController& operator=(const TestScreenController&) = delete;

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
