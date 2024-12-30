//
// Created by malac on 29/12/2024.
//
#include <iostream>
#include "myTest.h"

#include "EPD_Test.h"
#include "DEV_Config.h"
#include "EPD_7in5_V2.h"
#include "GUI_Paint.h"
#include "fonts.h"

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

void DrawText(UWORD xStart, UWORD yStart, const char text[], sFONT *Font,
              UWORD foreground, UWORD background) {
    UWORD dx = Font->Width;
    for (int i = 0; i < sizeof(text) - 1; i++) {
        Paint_DrawChar(xStart + dx * i, yStart, text[i], Font, foreground, background);
    }
}

void DISPLAY_TEXT(UBYTE *BLACK_IMAGE) {
    EPD_7IN5_V2_Init_Part();
    Paint_NewImage(BLACK_IMAGE, Font20.Width * 7, Font20.Height, 0, WHITE);
    Paint_SelectImage(BLACK_IMAGE);
    Paint_Clear(WHITE);

    const char text[] = "TESTTEST12";

    Paint_ClearWindows(0, 0, Font20.Width * 7, Font20.Height, WHITE);
    DrawText(0, 0, text, &Font20, WHITE, BLACK);
    EPD_7IN5_V2_Display_Part(BLACK_IMAGE, 150, 80, 150 + Font20.Width * 10, 80 + Font20.Height);

    DEV_Delay_ms(10000);

    DEV_Delay_ms(500); //Analog clock 1s
}

int my_test() {
    EPD_7in5_V2_test();

    // cout << ("Doing MY test!\n") << endl;
    //
    // if (DEV_Module_Init() != 0) {
    //     return -1;
    // }
    //
    // cout << "e-Paper Init and Clear..." << endl;
    // EPD_7IN5_V2_Init();
    // EPD_7IN5_V2_Clear();
    //
    // //Create a new image cache
    // UBYTE *BLACK_IMAGE;
    // const UDOUBLE IMAGE_SIZE = (EPD_7IN5_V2_WIDTH / 8) * EPD_7IN5_V2_HEIGHT;
    //
    // if ((BLACK_IMAGE = (UBYTE *) malloc(IMAGE_SIZE)) == NULL) {
    //     cout << "Failed to apply for black memory..." << endl;
    //     return -1;
    // }
    //
    // cout << "Paint_NewImage" << endl;
    // Paint_NewImage(BLACK_IMAGE, EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, GRAY2);
    //
    //
    // DEV_Delay_ms(1500);
    //
    // DISPLAY_TEXT(BLACK_IMAGE);
    //
    // EXIT();
    // free(BLACK_IMAGE);


    return 0;
}
