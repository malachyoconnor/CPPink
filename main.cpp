#include <myBmpManager.h>
#include <myGUI.h>

#include <csignal>
#include <format>
#include <random>

// Randomness settings
std::random_device rd;
std::mt19937 gen(rd());
using namespace std;

std::string update() {
    // Epoch was 01 Jan 1970
    auto seconds_since_epoch =
        std::chrono::system_clock::now().time_since_epoch().count() /
        1'000'000'000;

    auto seconds_into_today = seconds_since_epoch % (3600 * 24);
    auto hours = seconds_into_today / 3600;
    // Very basic conversion to my timezone - WIP
    hours += 1;
    auto minutes = (seconds_into_today % 3600) / 60;

    return std::format("{}:{}", hours, minutes);
}

int main() {
    // Ensure when we ctrl+c - the paper is shutdown
    signal(SIGINT, exit);

    try
    {
        Gui& screenController = Gui::createGui();

        screenController.DrawText(update(), {0, 0});
        screenController.DrawText(update(), {50, 50});
        screenController.DrawText(update(), {200, 100});
        screenController.DrawText("TESTING - Does this work? Seems so.", {150, 150});

        screenController.UpdateScreen();
        // screenController.UpdatePartOfScreen({0, 0}, {200, 200});

        // screenController.Sleep(5000);
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
        return 0;
    }
}
