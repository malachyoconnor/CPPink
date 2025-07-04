#ifndef BASEGUI_H
#define BASEGUI_H
#include "BaseScreenController.h"
#include "BoundaryBox.h"
#include "testScreenController.h"

class BaseScreenController;

class BaseGUI {
private:
   BaseGUI() = delete;

public:
   virtual ~BaseGUI() = default;

   BaseGUI(const BoundaryBox boundary, std::shared_ptr<BaseScreenController> screen_controller) : subWindow(boundary),
      screenController(screen_controller) {
   };

protected:
   BoundaryBox subWindow;
   std::shared_ptr<BaseScreenController> screenController;
};


#endif //BASEGUI_H
