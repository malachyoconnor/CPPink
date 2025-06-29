#include <csignal>
#include <format>
#include <fstream>
#include <random>

#include "bmpManager.h"
#include "helper_funcs.h"
#include "testScreenController.h"

using namespace std;

int main() {
   // Ensure when we ctrl+c - the paper is shutdown
   signal(SIGINT, exit);

   try {
      BaseScreenController& screenController = TestScreenController::createGui();

      screenController.DrawLine({0, 0}, {50, 100});

      while (true) {
         screenController.ClearScreen();
         auto l = get_weather();

         screenController.DrawText_(get_time(),{5, 5});

         for (size_t i = 0; i < l.size(); ++i) {
            screenController.DrawText_(l[i], {150, static_cast<int>(150 + 24 * i)});
         }

         screenController.UpdateScreen();
         screenController.Sleep(60 * 1000);
      }
   }
   catch (exception& e) {
      cout << e.what() << endl;
      return 0;
   }
}
