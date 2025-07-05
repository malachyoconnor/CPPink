#ifndef MYGUI_H
#define MYGUI_H

#include <array>
#include <memory>
#include <optional>
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

private:
   TestScreenController();
   std::array<std::array<UBYTE, EPD_7IN5_V2_WIDTH>, EPD_7IN5_V2_HEIGHT> pixels_{};
   BoundaryBox DrawChar(char toDraw, Point bottomLeft);

   void raylibScreenManager();
   std::thread screen_thread;
   std::atomic_bool screen_changed = false;
   std::optional<BoundaryBox> current_scissors = {};

public:
   ~TestScreenController();

   static std::shared_ptr<TestScreenController> createGui();

   TestScreenController(const TestScreenController&) = delete;

   TestScreenController& operator=(const TestScreenController&) = delete;

   void UpdateScreen() override;
   void ClearScreen() override;
   void PrintInternalArray() const override;
   void StartScissorsMode(BoundaryBox view) override;
   void EndScissorsMode() override;

   // void UpdatePartOfScreen(Point bottomLeft, Point topRight);

   void DrawBlackPixel(int x, int y) override;
   void DrawWhitePixel(int x, int y) override;
   void DrawLine(Point p1, Point p2) override;
   void DrawLineWithoutUpdating(Point p1, Point p2);
   void DrawRectangle(Point topLeft, Point bottomRight);
   void DrawRectangleWithoutUpdating(Point p1, Point p2);
   void DrawBMP(const BmpImage& image, Point bottomLeftBoundary) override;

   BoundaryBox DrawText_(std::string stringToDraw, Point bottomLeftBoundary) override;

   void Sleep(int millis);

   void SaveScreenToBmp(std::filesystem::path& path) const;
};

#endif  // MYGUI_H
