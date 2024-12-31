#include <iostream>
#include <EPD_Test.h>
#include <DEV_Config.h>
#include <EPD_7in5_V2.h>
#include <GUI_Paint.h>
#include <fonts.h>
#include <myBmpManager.h>
#include <myGUI.h>

using namespace std;

void EXIT() {
    cout << "Clear..." << endl;
    EPD_7IN5_V2_Init();
    EPD_7IN5_V2_Clear();

    cout << "Goto Sleep..." << endl;
    EPD_7IN5_V2_Sleep();
    // free(BlackImage);
    // BlackImage = NULL;
    DEV_Delay_ms(2000); //important, at least 2s
    // close 5V
    cout << "close 5V, Module enters 0 power consumption ..." << endl;
    DEV_Module_Exit();
}

void DrawText(UWORD xStart, UWORD yStart, const string &text, sFONT *Font,
              UWORD foreground, UWORD background) {
    UWORD dx = Font->Width;
    cout << text << text.size() << endl;
    cout << "WHATS HAPPENING" << endl;

    for (UWORD i = 0; i < 4; i++) {
        Paint_SetPixel(xStart + i * 5, yStart - 5, BLACK);
        // Paint_DrawChar(xStart + dx * i, yStart, 'a', Font, background, foreground);
    }
}

void DISPLAY_TEXT(UBYTE *BLACK_IMAGE) {
    const string text = "Test";

    EPD_7IN5_V2_Init_Part();
    Paint_NewImage(BLACK_IMAGE, Font20.Width * 4, Font20.Height, 0, WHITE);
    Paint_SelectImage(BLACK_IMAGE);
    Paint_Clear(WHITE);

    Paint_ClearWindows(0, 0, Font20.Width * 4, Font20.Height, WHITE);

    DrawText(0, 0, text, &Font20, WHITE, BLACK);

    EPD_7IN5_V2_Display_Part(BLACK_IMAGE, 150, 80, 150 + Font20.Width * 4, 80 + Font20.Height);

    DEV_Delay_ms(10000);
}

void my_Paint_DrawTime(UWORD Xstart, UWORD Ystart, PAINT_TIME *pTime, sFONT *Font,
                       UWORD Color_Foreground, UWORD Color_Background) {
    uint8_t value[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    UWORD Dx = Font->Width;

    cout << "WIDTH: " << Font20.Width * 7 << "HEIGHT: " << Font20.Height << endl;


    //Write data into the cache
    Paint_DrawChar(Xstart, Ystart, value[pTime->Hour / 10], Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + 14, Ystart, value[pTime->Hour % 10], Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + 14 * 2, Ystart, ':', Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + 14 * 2 + 11, Ystart, value[pTime->Min / 10], Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + 14 * 3 + 11, Ystart, value[pTime->Min % 10], Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + 14 * 4 + 11, Ystart, ':', Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + 14 * 4 + 11 * 2, Ystart, value[pTime->Sec / 10], Font, Color_Background, Color_Foreground);
    Paint_DrawChar(Xstart + 14 * 5 + 11 * 2, Ystart, value[pTime->Sec % 10], Font, Color_Background, Color_Foreground);
}

void SHOW_TIME_MVP(UBYTE *BLACK_IMAGE) {
    EPD_7IN5_V2_Init_Part();
    Paint_NewImage(BLACK_IMAGE, Font20.Width * 7, Font20.Height, 0, WHITE);
    Paint_SelectImage(BLACK_IMAGE);
    Paint_Clear(WHITE);

    Paint_ClearWindows(0, 0, Font20.Width * 7, Font20.Height, WHITE);

    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 12;
    sPaint_time.Sec = 12;

    // Paint_DrawTime()

    my_Paint_DrawTime(0, 0, &sPaint_time, &Font20, WHITE, BLACK);

    EPD_7IN5_V2_Display_Part(BLACK_IMAGE, 150, 80, 150 + Font20.Width * 7, 80 + Font20.Height);

    cin.ignore();
    DEV_Delay_ms(5000); //Analog clock 1s
}


int my_old_test() {
    cout << ("Doing my test!\n") << endl;

    if (DEV_Module_Init() != 0) {
        return -1;
    }

    cout << "e-Paper Init and Clear..." << endl;
    EPD_7IN5_V2_Init();
    EPD_7IN5_V2_Clear();

    //Create a new image cache
    UBYTE *BLACK_IMAGE;
    const UDOUBLE IMAGE_SIZE = (EPD_7IN5_V2_WIDTH / 8) * EPD_7IN5_V2_HEIGHT;

    if ((BLACK_IMAGE = (UBYTE *) malloc(IMAGE_SIZE)) == nullptr) {
        cout << "Failed to apply for black memory..." << endl;
        return -1;
    }

    cout << "Draw time" << endl;
    SHOW_TIME_MVP(BLACK_IMAGE);

    cout << "Paint_NewImage" << endl;
    Paint_NewImage(BLACK_IMAGE, EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, WHITE);
    DEV_Delay_ms(1500);

    DISPLAY_TEXT(BLACK_IMAGE);

    EXIT();
    free(BLACK_IMAGE);


    return 0;
}


int main() {
    Gui &screenController = Gui::instance();
    screenController.drawSomeStuff();

    screenController.saveBmpFile();
}
