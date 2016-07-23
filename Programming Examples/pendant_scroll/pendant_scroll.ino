/*
 * Matrchfire LED Matrix Pendant
 * http://www.matchfire.net
 * http://shop.matchfire.net/electronics/led-matrix-pendant.html
 * Uses Adafruit HT16K33 Matrix drivers
 * http://www.adafruit.com
 * https://learn.adafruit.com/adafruit-led-backpack
 * 
 * Scrolls the text "Matchfire"
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  matrix.begin(0x70);  // Built-in matrix at 0x70
  matrix.setBrightness(1); //Lower brightness for battery life.
  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  matrix.setTextColor(LED_ON);
}

void loop() {
  //scroll "Matchfire"
  for (int x = 8; x >=-54; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Matchfire");
    matrix.writeDisplay();
    delay(65);
  }
}
