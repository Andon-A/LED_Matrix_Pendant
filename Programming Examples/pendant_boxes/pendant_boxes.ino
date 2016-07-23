/*
 * Matrchfire LED Matrix Pendant
 * http://www.matchfire.net
 * http://shop.matchfire.net/electronics/led-matrix-pendant.html
 * Uses Adafruit HT16K33 Matrix drivers
 * http://www.adafruit.com
 * https://learn.adafruit.com/adafruit-led-backpack
 * 
 * A box that rotates within the confines of the screen
 * Grows and shrinks as the size changes.
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int pos = 0;
int in = 1;
int spd = 100;

void setup() {
  matrix.begin(0x70);  // Built-in matrix at 0x70
  matrix.setBrightness(1); //Lower brightness for battery life.
}

void loop() {
  pos += 1;
  if (pos > 6) {
    pos = 0;
    in = in * -1;
  }
  matrix.clear();
  drawBox();
  matrix.writeDisplay();
  delay(spd);
}

void drawBox () {
  matrix.drawLine(0,7-pos,pos,0,LED_ON);
  matrix.drawLine(7,pos,7-pos,7,LED_ON);
  matrix.drawLine(7-pos,7,0,7-pos,LED_ON);
  matrix.drawLine(pos,0,7,pos,LED_ON);
}

