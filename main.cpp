#include <csignal>
#include <myGUI.h>
#include <myBmpManager.h>
#include <random>

// Randomness settings
std::random_device rd;
std::mt19937 gen(rd());

using namespace std;

int main() {
    // Ensure when we ctrl+c - the paper is shutdown
    signal(SIGINT, exit);

    Gui &screenController = Gui::createGui();
    screenController.UpdatePartOfScreen({0, 0}, {400, 400});

    for (int i = 0; i < 10; i++) {
        screenController.DrawRectangleWithoutUpdating({i*10, i*10}, {400 - i*10, 400-i*10});
        screenController.Sleep(500);
        cout << i << endl;
    }

    screenController.DrawRectangleWithoutUpdating({10, 10}, {700, 400});

    screenController.UpdatePartOfScreen({0, 0}, {400, 400});
    screenController.Sleep(5000);

    screenController.UpdateScreen();

    screenController.Sleep(5000);
}
