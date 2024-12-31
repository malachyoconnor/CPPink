#include <iostream>
#include <EPD_Test.h>
#include <DEV_Config.h>
#include <EPD_7in5_V2.h>
#include <GUI_Paint.h>
#include <fonts.h>
#include <myBmpManager.h>
#include <myGUI.h>

using namespace std;

int main() {
    Gui &screenController = Gui::instance();
    screenController.drawSomeStuff();

    screenController.saveBmpFile();
}
