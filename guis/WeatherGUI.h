#ifndef TRAINGUI_H
#define TRAINGUI_H
#include <utility>

#include "helper_funcs.h"
#include "../utils/BaseGUI.h"

class WeatherGui : public BaseGUI {
public:
   WeatherGui(const BoundaryBox boundary, std::shared_ptr<BaseScreenController> screen_controller) : BaseGUI(
      boundary, std::move(screen_controller)) {
   };

   void Render() override {
      // screenController->StartScissorsMode(subWindow);
      auto weather_lines = get_weather_text();

      screenController->DrawText_(get_time(), {5, 5});

      for (size_t i = 0; i < weather_lines.size(); ++i) {
         screenController->DrawText_(weather_lines[i], {
                                        150,
                                        static_cast<int>(150 + 24 * i)
                                     });
      }
      // screenController->EndScissorsMode();
   }
};


#endif //TRAINGUI_H
