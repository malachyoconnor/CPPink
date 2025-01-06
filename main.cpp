#include <myBmpManager.h>
#include <myGUI.h>

#include <csignal>
#include <random>

// Randomness settings
std::random_device rd;
std::mt19937 gen(rd());

using namespace std;

int main() {
   // Ensure when we ctrl+c - the paper is shutdown
   signal(SIGINT, exit);

   Gui &screenController = Gui::createGui();

   screenController.DrawText("TESTING - Does this work? Seems so.", {150, 150});
   screenController.UpdateScreen();
   screenController.Sleep(5000);
}
