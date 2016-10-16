/*
 * Matrchfire LED Matrix Pendant
 * http://www.matchfire.net
 * http://shop.matchfire.net/electronics/led-matrix-pendant.html
 * Uses Adafruit HT16K33 Matrix drivers
 * http://www.adafruit.com
 * https://learn.adafruit.com/adafruit-led-backpack
 * 
 * Scrolls the text string "str" (How original!)
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

char* str = "Matchfire";

void scrollText(char* txt, int spd = 85) {
  //Scroll a given bit of text.
  int scmin = -6 * strlen(txt); //Set amount of scroll for text length
  for (int x = 8; x >=scmin; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print(txt);
    matrix.writeDisplay();
    delay(spd);
  }
}

void setup() {
  matrix.begin(0x70);  // Built-in matrix at 0x70
  matrix.setBrightness(1); //Doesn't affect battery life much, but helps with cameras
  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  matrix.setTextColor(LED_ON);
}

void loop() {
  //Scroll the text "Matchfire"
  scrollText(str);
}
