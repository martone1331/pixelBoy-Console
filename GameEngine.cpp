#include "GameEngine.h"

GameEngine::GameEngine(int joyPorts[3], int btnPorts[4], int buzzer_port, LedControl* lc, U8G2_SH1106_128X64_NONAME_F_HW_I2C* in_OLED){
    JOY_X = joyPorts[0];
    JOY_Y = joyPorts[1];
    JOY_BUTN = joyPorts[2];

    BUTN1 = btnPorts[0];
    BUTN2 = btnPorts[1];
    BUTN3 = btnPorts[2];
    BUTN4 = btnPorts[3];

    BUZZ = buzzer_port;

    LEDcontrol = lc;
    OLED = in_OLED;
}

/*===========================================
  ==-------------DISPLAY METHODS-----------==
  =========================================== */

void GameEngine::setPixel(int x, int y, int set){

    //Invert the axes for a flipped display
    x = 15-x;
    y = 7-y;

    //Handle invalid inputs
    if (x > 15 || y > 7){
    return;
    }

    //Setting for display 1
    if (15 >= x && x >= 8 && set==1){
    displayCol1[x-8] |= 1 << y;
    }
    else if (set==0){
    displayCol1[x] &= ~(1 << y);
    }

    //Setting for display 0
    if (7 >= x && x >= 0 && set==1){
    displayCol0[x] |= 1 << y;
    }
    else if (set==0){
    displayCol0[x] &= ~(1 << y);
    }
}

void GameEngine::clearPixels(){

    for(int i = 0; i< sizeof(displayCol0); i++){
        displayCol0[i] = B00000000;
    }
    for(int j = 0; j<sizeof(displayCol1); j++){
        displayCol1[j] = B00000000;
    }
}

void GameEngine::renderFrame(){
    for (int cols=0; cols < 8; cols++){
        LEDcontrol->setRow(0, cols, displayCol0[cols]);
        LEDcontrol->setRow(1, cols, displayCol1[cols]);
      }
}

void GameEngine::drawTextOLED(int x, int y, const char* text, bool invert, const uint8_t* font){
  OLED->setFont(font);        
  OLED->setBitmapMode(invert);
  OLED->drawStr(x, y, text);
}

/*void GameEngine::drawCharacter(int x, int y, String font, int mychar){
  OLED->setFont(font);        
  OLED->drawStr(text)
}*/

void GameEngine::clearOLEDBuffer(){
  OLED->clearBuffer();
}

void GameEngine::sendOLEDBuffer(){
  OLED->sendBuffer();
}

/*===========================================
  ==---------INITIALIZATION METHODS--------==
  =========================================== */

void GameEngine::setupDisplays(){

  //Turn on LED matrices and set brightness
    LEDcontrol->shutdown(0, false);
    LEDcontrol->shutdown(1, false);
    LEDcontrol->setIntensity(0, brightness);
    LEDcontrol->setIntensity(1, brightness);
    LEDcontrol->clearDisplay(0);
    LEDcontrol->clearDisplay(1);

  //Turn on OLED display
    OLED->setI2CAddress(0x078);
    OLED->begin();
}

void GameEngine::setupInputs(){
    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);
    pinMode(JOY_BUTN, INPUT);
    pinMode(BUTN1, INPUT);
    pinMode(BUTN2, INPUT);
    pinMode(BUTN3, INPUT);
    pinMode(BUTN4, INPUT);
}

/*===========================================
  ==-----------CONTROLLER METHODS----------==
  =========================================== */

void GameEngine::joy_yMapping(){
  //Serial.println(analogRead(JOY_Y));
    if (analogRead(JOY_Y) > 3500){
        joy_y = 1;
      }
      else if (analogRead(JOY_Y) < 1500){
        joy_y = -1;
      }
      else {
        joy_y = 0;
      }
}
void GameEngine::joy_xMapping(){
    if (analogRead(JOY_X) > 1600){
        joy_x = 1;
      }
      else if (analogRead(JOY_X) < 600){
        joy_x = -1;
      }
      else {
        joy_x = 0;
      }
}
void GameEngine::getInputs(){
    joy_yMapping();
    joy_xMapping();

    button1 = digitalRead(BUTN1);
    button2 = digitalRead(BUTN2);
    button3 = digitalRead(BUTN3);
    button4 = digitalRead(BUTN4);
}

void GameEngine::playNote(int note , int duration){
    tone(BUZZ, note, duration);
}

void GameEngine::getTime(){
     time = millis();
}

