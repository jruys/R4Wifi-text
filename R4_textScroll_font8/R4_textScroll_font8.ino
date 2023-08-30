#include "Arduino_LED_Matrix.h"
#include "font8.h"

ArduinoLEDMatrix matrix;

#define DISPLAY_COLUMNS 12
#define DISPLAY_ROWS 12

uint8_t frame[DISPLAY_ROWS][DISPLAY_COLUMNS];

byte *LED_GetFontStart(byte code) {
  byte *p;
  byte current;

  current = 0;
  p = g_font;

  while (*p != 255) {
    if (code == current) {
      return p;
    }
 // skip the font data
    p += *p;
 // skip always one byte of font count itself
    p++;
    current++;
  }
  return 0;
}
int LED_displayArray(byte *p, int devs, int ofs)
{
  int drawn = 0;
  for(int i = 0; i < devs; i++) {
    int di = ofs + i;
    if(di < 0)
      continue; // skip
    if(di >= DISPLAY_COLUMNS)
      break; //dont go outside array
    for(int j = 0; j < 8; j++) {
      frame[j][di] = !!(p[i] & (1<<(j)));
    }
    drawn++;
  }
    return drawn;

}
int LED_print(int ofs, const char *p) {
  int drawn = 0;
  byte *font;
  byte zero = 0;

  while (*p) {
    font = LED_GetFontStart(*p);
    if (font) {
      drawn += LED_displayArray(font+1, *font, ofs);
      ofs += *font;
      drawn += LED_displayArray(&zero, 1, ofs);
      ofs++;
    }
    p++;
  }
  return drawn;
}

void setup() {
 // put your setup code here, to run once:
  Serial.begin(115200);
  delay(150);
  matrix.begin();
  delay(1000);
}

char* text=" Far out in the uncharted backwaters of the unfashionable end of the western spiral arm of the Galaxy lies a small unregarded yellow sun. Orbiting this at a distance of roughly ninety-two million miles is an utterly insignificant little blue green planet whose ape-descended life forms are so amazingly primitive that they still think digital watches are a pretty neat idea... ";
//char* text="0123456789 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ -- ";

int ofs = DISPLAY_COLUMNS;
void loop() {
  delay(50);
  memset(frame,0,sizeof(frame));
  if(LED_print(ofs,text) == 0 && ofs < 0) {
    ofs = DISPLAY_COLUMNS;
  } else {
    ofs--;
  }
   matrix.renderBitmap(frame, DISPLAY_ROWS, DISPLAY_COLUMNS);
}
