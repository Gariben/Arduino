
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
int gRedPin = 3;
int gGreenPin = 4;
int gBluePin  = 5;

#define RGB_OFF {0,0,0};
#define RGB_RED {255, 0, 0};
#define RGB_ORANGE {255, 10, 0};
#define RGB_YELLOW {255, 40, 0};
#define RGB_GREEN {0, 255, 0};
#define RGB_BLUE {0, 0, 255};
#define RGB_PINK {128, 0, 128};
#define RGB_WHITE { 255, 255, 255};

#define STRIP_OFF    0x000000
#define STRIP_RED    0xFF0000
#define STRIP_GREEN  0x00FF00
#define STRIP_BLUE   0x0000FF
#define STRIP_YELLOW 0xFFFF00
#define STRIP_PINK   0xFF1088
#define STRIP_ORANGE 0xE05800
#define STRIP_WHITE  0xFFFFFF


struct rgb {
  int iRed = 0;
  int iGreen = 0;
  int iBlue = 0;
};



rgb rgbRainbow[8];
int intRainbow[8];
int giRainbowMax = 8;
void BuildRainbows() {
  rgbRainbow[0] = RGB_OFF;
  rgbRainbow[1] = RGB_RED;
  rgbRainbow[2] = RGB_ORANGE;
  rgbRainbow[3] = RGB_YELLOW;
  rgbRainbow[4] = RGB_GREEN;
  rgbRainbow[5] = RGB_BLUE;
  rgbRainbow[6] = RGB_PINK;
  rgbRainbow[7] = RGB_WHITE;

  intRainbow[0] = STRIP_OFF;
  intRainbow[1] = STRIP_RED;
  intRainbow[2] = STRIP_ORANGE;
  intRainbow[3] = STRIP_YELLOW;
  intRainbow[4] = STRIP_GREEN;
  intRainbow[5] = STRIP_BLUE;
  intRainbow[6] = STRIP_PINK;
  intRainbow[7] = STRIP_WHITE;
};



void Buildrgb(int iStripPin, int iRedPin, int iGreenPin, int iBluePin) {
  strip.begin();
  strip.show();
  BuildRainbows();
  gStripPin = iStripPin;
  gRedPin = iRedPin;
  gGreenPin = iGreenPin;
  gBluePin = iBluePin;
};

void Buildrgb() {
  //Defaults
  Buildrgb(2,3,4,5);
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
  rgb rgbColor = rgbRainbow[iColor];
  int stripColor = intRainbow[iColor];
  
  //RGB light-----------------------------------------------------
  constrain(rgbColor.iRed,0,255);
  constrain(rgbColor.iGreen,0,255);
  constrain(rgbColor.iBlue,0,255);
  constrain(iBright,0,100);

  float fBright = ((float)iBright / (float)100.0);
  
  analogWrite(gRedPin, (int)((float)rgbColor.iRed*(float)fBright));
  analogWrite(gGreenPin, (int)((float)rgbColor.iGreen*(float)fBright));
  analogWrite(gBluePin, (int)((float)rgbColor.iBlue*(float)fBright));

  //WS2812B Strip------------------------------------------------

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
