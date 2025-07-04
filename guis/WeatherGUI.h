#ifndef TRAINGUI_H
#define TRAINGUI_H
#include <iostream>
#include <utility>

#include "../utils/BaseGUI.h"

class WeatherGui : public BaseGUI {
public:
   WeatherGui(const BoundaryBox boundary, std::shared_ptr<BaseScreenController> screen_controller) : BaseGUI(
      boundary, std::move(screen_controller)) {
   };

   void test_working() {
      std::cout << "test_working" << std::endl;
   }
};


#endif //TRAINGUI_H
