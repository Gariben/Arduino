
#ifndef _Rgb_h
#ifdef __cplusplus
#define _Rgb_h

//rgb LED and W2812B Strip library.
#include <OctoWS2811.h>

//WS2812B Boilerplate
const int ledsPerStrip = 20;
DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 strip(ledsPerStrip, displayMemory, drawingMemory, config);

//defult pins. Tehse can be overriden later.
int gStripPin = 2;

#define STRIP_OFF    0x000000
#define STRIP_RED    0xFF0000
#define STRIP_GREEN  0x00FF00
#define STRIP_BLUE   0x0000FF
#define STRIP_YELLOW 0xFFFF00
#define STRIP_PINK   0xFF1088
#define STRIP_ORANGE 0xE05800
#define STRIP_WHITE  0xFFFFFF

int intRainbow[8];
int giRainbowMax = 8;
void BuildRainbows() {


  intRainbow[0] = STRIP_OFF;
  intRainbow[1] = STRIP_RED;
  intRainbow[2] = STRIP_ORANGE;
  intRainbow[3] = STRIP_YELLOW;
  intRainbow[4] = STRIP_GREEN;
  intRainbow[5] = STRIP_BLUE;
  intRainbow[6] = STRIP_PINK;
  intRainbow[7] = STRIP_WHITE;
};



void Buildrgb(int iStripPin) {
  strip.begin();
  strip.show();
  BuildRainbows();
  gStripPin = iStripPin;
};

void Buildrgb() {
  //Defaults
  Buildrgb(2);
};

//WS2812B Functions


void StripWipe(int iStripColor, int iMSWait)
{
  for (int i=0; i < strip.numPixels(); i++) {
    strip.setPixel(i, iStripColor);
    strip.show();
    delayMicroseconds(iMSWait);
  }
}

void StripWipe(int iStripColor)
{
  StripWipe(iStripColor,0);
}





//Master 


void LIGHTS_ON(int iColor, int iBright) {
  constrain(iColor,0,7);
  int stripColor = intRainbow[iColor];
  StripWipe(stripColor);
}

void LIGHTS_ON(int iColor) {
  LIGHTS_ON(iColor, 100);
}

void LIGHTS_OFF() {
  LIGHTS_ON(0, 0);
}


#endif // __cplusplus
#endif /* _Time_h */
