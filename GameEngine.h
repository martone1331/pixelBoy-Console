#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <Arduino.h>
#include "LedControl.h"
#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
/*#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> */


class GameEngine{

private:
// =====JOYSTICK PORTS=====:
    int JOY_X;
    int JOY_Y;
    int JOY_BUTN;

// ======BUTTON PORTS======:
    int BUTN1;
    int BUTN2;
    int BUTN3;
    int BUTN4;
 
public:
//Constructor:
    GameEngine(int joyPorts[3], int btnPorts[4], int buzzer_port, LedControl* lc, U8G2_SH1106_128X64_NONAME_F_HW_I2C* in_OLED);
    
//Led Controller from library
    LedControl* LEDcontrol;

// Adafruit OLED from library
    U8G2_SH1106_128X64_NONAME_F_HW_I2C* OLED;

//Global Time
    unsigned long time;

//Arrays that handle pixels to be displayed
    unsigned char displayCol0[8];
    unsigned char displayCol1[8];

// =====DISPLAY METHODS=====:
    void setPixel(int x, int y, int set);
    void clearPixels();
    void renderFrame();
    void setupDisplays();
    void drawTextOLED(int x, int y, const char* text, bool invert = false, const uint8_t* font = u8g2_font_helvB12_tr);
    void sendOLEDBuffer();
    void clearOLEDBuffer();

// =====INPUT METHODS=====:
    void setupInputs();
    void joy_yMapping();
    void joy_xMapping();
    void getInputs();

// =====SOUNDS METHODS=====:
    void playNote(int note, int duration);

// =====GLOBAL METHODS=====:
    void getTime();

// =====PIEZO BUZZER=====:
    int BUZZ;

// =====CONTROLLER VARIABLES=====:
    int joy_x;
    int joy_y;
    int last_joy_y;
    int last_joy_x;
    boolean button1 = LOW;
    boolean button2 = LOW;
    boolean button3 = LOW;
    boolean button4 = LOW;

// =====DISPLAY VARIABLES=====:
    float brightness = 2;
    #define OLED_ADDRESS 0x78

};

#endif 