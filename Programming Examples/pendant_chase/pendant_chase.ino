/*
 * Matrchfire LED Matrix Pendant
 * http://www.matchfire.net
 * http://shop.matchfire.net/electronics/led-matrix-pendant.html
 * Uses Adafruit HT16K33 Matrix drivers
 * http://www.adafruit.com
 * https://learn.adafruit.com/adafruit-led-backpack
 * 
 * Bounces a 'Pony' across the screen.
 * It's only 8x8 pixels, don't expect much.
  */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int x = 8;
int y = 3;

static const uint8_t PROGMEM
  pony_bmp[] =
  { B0100000,
    B1100010,
    B0011101,
    B0010101,
    B0010100 },
  ponyR_bmp[] =
  { B0000010,
    B0100011,
    B1011100,
    B1010100,
    B0010100 },
  peg_bmp[] = 
  { B00011100,
    B01011000,
    B11010111,
    B00111000,
    B01101100 },
  pegR_bmp[] = 
  { B00111000,
    B00011010,
    B11101011,
    B00011100,
    B00110110 };

void scrollText(char* txt, int spd = 65) {
  //Scroll a given bit of text.
  //For some reason, when used with the scrollPony,
  //It'll only display a letter when the previous letter is completely off screen.
  int scmin = -6 * strlen(txt); //Set amount of scroll for text length
  for (int tx = 8; tx >=scmin; tx--) {
    matrix.clear();
    matrix.setCursor(tx,0);
    matrix.print(txt);
    matrix.writeDisplay();
    delay(spd);
  }
}

void drawPony(int xpos, int ypos, int del, int pny){
  matrix.clear();
  if (pny == 1){
    matrix.drawBitmap(xpos, ypos, peg_bmp, 8, 5, LED_ON);
  }
  else if (pny == 2) {
    matrix.drawBitmap(xpos, ypos, ponyR_bmp, 8, 5, LED_ON);
  }
  else if (pny == 3) {
    matrix.drawBitmap(xpos, ypos, pegR_bmp, 8, 5, LED_ON);
  }
  else {
  matrix.drawBitmap(xpos, ypos, pony_bmp, 8, 5, LED_ON);
  }  
  matrix.writeDisplay();
  delay(del);
}

void scrollPony(int ypos, int spd=100, int pny=0, bool bounce = true, bool left = true) {
  //"Scrolls" a pony from one side of the screen to the other.
  //Four options:
    // 0: Left-facing Pony
    // 1: Left-facing Pegasus
    // 2: Right-facing Pony
    // 3: Right-Facing Pegasus
  //Alicorns/Unicorns can't be done at this resolution

  if (left) { //Left to right
    //If we bounce/walk:  
    if (bounce) {
      for (int xpos = 8; xpos >= -8; xpos--) {
        drawPony(xpos, ypos, spd, pny);
        drawPony(xpos, ypos-1, spd, pny);
        drawPony(xpos-1, ypos-1, spd, pny);
      }
    }
    //If we fly/slide:
    else {
      for (int xpos = 8; xpos >= -8; xpos--) {
        drawPony(xpos, ypos, spd, pny);
      }
    }
  }
  else {//Right to left
    //If we bounce/walk:  
    if (bounce) {
      for (int xpos = -8; xpos <= 8; xpos++) {
        drawPony(xpos, ypos, spd, pny);
        drawPony(xpos, ypos-1, spd, pny);
        drawPony(xpos+1, ypos-1, spd, pny);
      }
    }
    //If we fly/slide:
    else {
      for (int xpos = -8; xpos <= 8; xpos++) {
        drawPony(xpos, ypos, spd, pny);
      }
    }
  }
}

void setup() {
  matrix.begin(0x70);  // Built-in matrix at 0x70
  matrix.setBrightness(1); //Lower brightness for battery life.
  // put your setup code here, to run once:

}

void loop() {
  scrollPony(3);
  delay(250);
  scrollPony(1,80,1,false);
  delay(250);
  scrollPony(3,100,2,true,false);
  delay(250);
  scrollPony(1,80,3,false,false);
  delay(250);
}
