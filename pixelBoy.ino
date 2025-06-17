#include "GameEngine.h"
#include "Game.h"
#include "Pong.h"
#include "Tetris.h"
#include "LedControl.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <u8g2lib.h>
/*#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>*/


#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1

int joy_ports[3] = {13, 12, 14}; //Vx, Vy, BTN
int button_ports[4] = {16,18,17,19}; // BUTN 1-4
int buzzer_port = 15;

LedControl lc = LedControl(27,25,26,2); //DATAIN, CLK, CS
U8G2_SH1106_128X64_NONAME_F_HW_I2C OLED(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//Adafruit_SSD1306 displayTest(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

GameEngine engine(joy_ports, button_ports, buzzer_port, &lc, &OLED);
Pong pong(engine);
Tetris tetris(engine);
Game* currentGame;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
  engine.setupDisplays();
  engine.setupInputs();
  currentGame = &pong;
}

void loop() {
  engine.getTime();
  engine.getInputs();
  currentGame->update();
}
