#include <myBmpManager.h>
// #include <myGUI.h>
#include <testGUI.h>

#include <csignal>
#include <format>
#include <random>

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
        BaseGUI& screenController = TestGui::createGui();

        screenController.DrawLine({0, 0}, {50, 100});

        screenController.DrawText_(update(), {30, 30});
        screenController.DrawText_(update(), {50, 50});
        screenController.DrawText_(update(), {200, 100});
        screenController.DrawText_("TESTING - Does this work? Seems so.", {150, 150});

    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
        return 0;
    }
}
