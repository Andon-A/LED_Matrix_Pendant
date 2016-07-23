/*
 * Matrchfire LED Matrix Pendant
 * http://www.matchfire.net
 * http://shop.matchfire.net/electronics/led-matrix-pendant.html
 * Uses Adafruit HT16K33 Matrix drivers
 * http://www.adafruit.com
 * https://learn.adafruit.com/adafruit-led-backpack
 * 
 * "Slow Fill" example
 * Starts at top/left and progressively turns each LED on.
 * Goes left to right, top to bottom.
 * Then rotates screen 90 degrees clockwise, and turns them off.
 * Rotates screen again, and repeats.
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int x = 0; //Starting position of ball.
int y = 0; //Starting height of ball.
int spd = 50; //MS between updates
int rot = 0; //Screen rotation
int d = 1; //1 = draw dot, 0 = clear dot

void setup() {
  matrix.begin(0x70);  // Built-in matrix at 0x70
  matrix.setBrightness(1); //Lower brightness for battery life.
  //Draw the dot's starting position.
  drawDot();
}

void loop() {
  x += 1;
  if (x > 7) {
    x = 0;
    y += 1;
  }
  if (y > 7) {
    y = 0;
    change();
  }
  if (d == 1) {
    drawDot();
  }
  else {
    clearDot();
  }
}

void drawDot(){
  //matrix.clear();
  matrix.drawPixel(x, y, LED_ON);
  matrix.writeDisplay();
  delay(spd);
}

void clearDot() {
  matrix.drawPixel(x, y, LED_OFF);
  matrix.writeDisplay();
  delay(spd);
}

void change(){
  rot += 1;
  if (rot > 3) {
    rot = 0;
  }
  matrix.setRotation(rot);
  if (d == 1) {
    d = 0;
  }
  else {
    d = 1;
  }
}

