
#ifndef _Rgb_h
#ifdef __cplusplus
#define _Rgb_h

//rgb LED and W2812B Strip library.
#include <OctoWS2811.h>

//WS2812B Boilerplate
const int gStripMax = 20;
DMAMEM int displayMemory[gStripMax*6];
int drawingMemory[gStripMax*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 strip(gStripMax, displayMemory, drawingMemory, config);

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

//Thread vars
volatile int gBackgroundColor = STRIP_OFF;
volatile int gThreadColor=STRIP_OFF;
volatile int gThreadPattern=0;
volatile int gThreadIndex=0;
volatile int gMSDelay=20000;

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

//Background Layer Functions--------------------------|

void BackgroundWipe(int iBGC, int iMSWait, bool bForwards)
{
  gBackgroundColor=iBGC;
  for (int i=0; i < strip.numPixels(); i++) {
    strip.setPixel(i, intRainbow[iBGC]);
    delayMicroseconds(iMSWait);
    strip.show();

  }
}

void BackgroundFill(int iBGC)
{
  BackgroundWipe(iBGC,0, true);
}

//Foreground Functions--------------------------------|
//All use thread's index/clock

void ForegoundBand(int i, int iFGC, int iBandLength, int iDirection){
  strip.setPixel(i, intRainbow[iFGC]);
  if(i>0)
    strip.setPixel(i-1, intRainbow[gBackgroundColor]);
  else if(i==0)
    strip.setPixel(gStripMax-1, intRainbow[gBackgroundColor]);
  strip.show();
}

void ErasePattern(int iOctave){
  //TODO: Cleanup

  if(iOctave==0){
    BackgroundFill(STRIP_OFF);
  }else{
      gThreadColor=STRIP_OFF;
      BackgroundFill(gBackgroundColor);
      gThreadPattern=0;    
  }
}


void DisplayPattern(int iColor, int iOctave){
      if(gDebug)
        Serial.println("\tDisplayPattern()");  
  gThreadColor=iColor;

  switch(iOctave){
    case 0:
      //Display Background Color
      if(gDebug)
        Serial.println("\tBackground Fill");
      BackgroundFill(iColor);
      break;
    case 1:
      if(gDebug)
        Serial.println("\tForeground Band");
      gThreadPattern=1;
      break;
    default:
      break;
  }
}

//Thread

//TODO: Write this code to be templatable.
void thread_LED(){
  while(1){
    //Update light index according to independent thread timer.
    //Only show if the midi listener asks for it.
    

      switch(gThreadPattern){
      case 0:
        //Don't show lights, but keep time.
        break;
      case 1:
        if(gDebug)
          Serial.println("\t\tThread: Foreground Band");
        ForegoundBand(gThreadIndex,gThreadColor,1,0);
        break;
      default:
        break;
      }
    
    if(gDebug){
      //Serial.println("\tFOREGROUND THREAD: ");
      //Serial.print("\t\t Color: ");
      //Serial.println(gThreadColor);
    }
    delayMicroseconds(gMSDelay);
    gThreadIndex++;
    if(gThreadIndex>=gStripMax)
      gThreadIndex=0;
  }
}






//Master


#endif // __cplusplus
#endif /* _Time_h */
