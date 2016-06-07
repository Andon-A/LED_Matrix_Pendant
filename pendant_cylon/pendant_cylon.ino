/*
 * Matrchfire LED Matrix Pendant
 * http://www.matchfire.net
 * http://shop.matchfire.net/electronics/led-matrix-pendant.html
 * Uses Adafruit HT16K33 Matrix drivers
 * http://www.adafruit.com
 * https://learn.adafruit.com/adafruit-led-backpack
 * 
 * 
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int x = 2; //Starting position of scanner
int xspd = 1; //How fast the scanner goes.

void setup() {
  matrix.begin(0x70);  // Built-in matrix at 0x70
  matrix.setBrightness(1); //Lower brightness for battery life.
  //Draw the ball's starting position.
  drawBall();
}

static const uint8_t PROGMEM
  neutral_bmp[] =
  { B00011000,
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B01011010,
    B10111101,
    B11111111 };

void loop() {
  //Add the X speed to the X position, unless we're going backwards.
  x += xspd;
  //Now check if they're out of bounds.
  if (x > 5) {
    //We are. Reverse the speed.
    x = 4;
    xspd = -1;
  }
  if (x < 2) {
    //Too low! Reverse again.
    x = 3;
    xspd = 1;
  }
  //Draw the ball
  drawBall();
}

void drawBall(){
  matrix.clear();
  matrix.drawBitmap(0,0, neutral_bmp, 8,8, LED_ON);
  //matrix.drawPixel(x, 2, LED_ON);
  matrix.drawPixel(x, 3, LED_ON);
  matrix.writeDisplay();
  delay(200);
}

