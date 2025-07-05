#include <csignal>
#include <format>
#include <fstream>
#include <random>

#include "utils/bmpManager.h"
#include "helper_funcs.h"
#include "testScreenController.h"
#include "WeatherGUI.h"

using namespace std;

int main() {
   // Ensure when we ctrl+c - the paper is shutdown
   signal(SIGINT, exit);

   try {
      std::shared_ptr<BaseScreenController> screenController = TestScreenController::createGui();
      auto weather = WeatherGui(BoundaryBox{{50, 50}, {450, 450}},
                                      screenController);

      while (true) {
         weather.Render();

         screenController->UpdateScreen();
         screenController->Sleep(5 * 1000);
      }
   } catch (exception &e) {
      cout << e.what() << endl;
      return 0;
   }
}
