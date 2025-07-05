#ifndef BASEGUI_H
#define BASEGUI_H
#include <utility>

#include "BaseScreenController.h"
#include "BoundaryBox.h"

class BaseGUI {
private:
   BaseGUI() = delete;

public:
   virtual ~BaseGUI() = default;

   BaseGUI(const BoundaryBox boundary, std::shared_ptr<BaseScreenController> screen_controller) : subWindow(boundary),
      screenController(std::move(screen_controller)) {
   };

   virtual void Render() = 0;

protected:
   BoundaryBox subWindow;
   std::shared_ptr<BaseScreenController> screenController;
};


#endif //BASEGUI_H
