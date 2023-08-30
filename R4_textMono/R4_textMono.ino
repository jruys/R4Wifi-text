#include "font8x8_basic.h"


byte frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;



void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.renderBitmap(frame, 8, 12);
}

void loop() {
  delay(1000);
  char* text=" Far out in the uncharted backwaters of the unfashionable end of the western spiral arm of the Galaxy lies a small unregarded yellow sun. Orbiting this at a distance of roughly ninety-two million miles is an utterly insignificant little blue green planet whose ape-descended life forms are so amazingly primitive that they still think digital watches are a pretty neat idea... ";
  for(int i=0; i<strlen(text); i++)
    for(int row=0; row<8; row++) {
      for(int col=0; col<8; col++)
        frame[col][11]=(font8x8_basic[text[i]][col]>>row) & 1; // I need to rotate colums as font is given as rows instead of columns
      left_scroll();
      matrix.renderBitmap(frame, 8, 12);
      delay(50);
    } 
  
}

void left_scroll() {
  for(int col=0; col<11; col++)
    for(int row=0; row<8; row++)
      frame[row][col]=frame[row][col+1];

}
