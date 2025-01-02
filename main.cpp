#include <EPD_Test.h>
#include <myGUI.h>

#include "myBmpManager.h"

using namespace std;

int main() {
    unique_ptr<BmpImage> bmp = OpenBMP("pic/randomTest.bmp");

    Gui &screenController = Gui::instance();
    screenController.drawSomeStuff();
    screenController.drawBMP(*bmp);

    screenController.saveScreenToBmp();
}
