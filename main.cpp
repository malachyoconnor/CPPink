#include <EPD_Test.h>
#include <myGUI.h>

#include "myBmpManager.h"

using namespace std;

int main() {
    unique_ptr<BmpImage> bmp = OpenBMP("pic/myTestImage.bmp");

    Gui &screenController = Gui::createGui();
    // screenController.DrawRectangle();
    screenController.drawBMP(*bmp);

    screenController.saveScreenToBmp();
}
