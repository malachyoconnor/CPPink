#include <EPD_Test.h>
#include <myGUI.h>

using namespace std;

int main() {
    Gui &screenController = Gui::instance();
    screenController.drawSomeStuff();

    screenController.saveBmpFile();
}
