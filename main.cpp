#include <myGUI.h>
#include <myBmpManager.h>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

using namespace std;

int main() {
    unique_ptr<BmpImage> const bmp = OpenBMP("pic/myTestImage.bmp");

    Gui &screenController = Gui::createGui();

    std::uniform_int_distribution<> randomX(0, EPD_7IN5_V2_WIDTH);
    std::uniform_int_distribution<> randomY(0, EPD_7IN5_V2_HEIGHT);

    screenController.DrawRectangleWithoutUpdating({10, 10}, {100, 150});

    Point prev = {randomX(gen), randomY(gen)};
    for (int i = 0; i < 10; ++i) {
        Point next = {randomX(gen), randomY(gen)};
        screenController.DrawRectangleWithoutUpdating(prev, next);
        prev = next;
    }

    screenController.UpdateScreen();

    for (int i = 0; i < 100; ++i) {
        Point next = {randomX(gen), randomY(gen)};
        screenController.DrawLineWithoutUpdating(prev, next);
        prev = next;
    }

    screenController.UpdateScreen();


    // screenController.DrawRectangleWithoutUpdating();
    // screenController.DrawBMP(*bmp);

    // screenController.SaveScreenToBmp();
}
