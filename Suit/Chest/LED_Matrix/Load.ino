#include "Adafruit_GFX.h"
#include "Adafruit_HT1632.h"

const bool bDebug = false;
const int iScreenWidth = 24;
const int iLoadSize = iScreenWidth - 2;
const bool bInvert = false;
const bool bDraw = !bInvert;

#define HT_DATA 2
#define HT_WR 3
#define HT_CS 4

Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);


void DrawLoadingBox(int iX, int iY, int iBarLength, int iBarSize) {
  //only 22 pixel loading screen atm, but can be expanded.
  iBarLength+=2;
  matrix.drawFastHLine(1, iY, iBarLength - 4, bDraw);
  matrix.drawFastVLine(0, iY + 1, iBarSize, bDraw);
  matrix.drawFastVLine(iBarLength-3, iY + 1, iBarSize, bDraw);
  matrix.drawFastHLine(1, iY + iBarSize + 1, iBarLength - 4, bDraw);
};

void DrawLoadZone(int iPercent, int iBarLength, int iBarHeight, int iX, int iY) {
  if (bDebug) {
    Serial.println("---Load Draw---");
    Serial.print("Initial Value: ");
    Serial.println(iPercent);
  }
  if (iPercent < 0)
    iPercent = 0;

  if (iPercent > 100)
    iPercent = 100;

  iPercent = iPercent / ((float)100/iBarLength);
  if (bDebug) {
    Serial.print("Bar Length: ");
    Serial.println(iBarLength);
    Serial.print("Ratio: ");
    Serial.println((float)100/iBarLength);
    Serial.print("Value in panels: ");
    Serial.println(iPercent);
  }
  matrix.fillRect(iX, iY, iPercent, iBarHeight, bDraw);


}


void FlashLoadZone(int iPercent, int iBarLength, int iBarHeight, int iX, int iY, int iDuration) {
  for (int8_t b = 15; b >= 0; b--) {
    DrawLoadZone(iPercent, iBarLength, iBarHeight, iX, iY);
    matrix.setBrightness(b);
    delay((iDuration / 2) / 16);
  }

  for (uint8_t b = 0; b < 16; b++) {
    DrawLoadZone(iPercent, iBarLength, iBarHeight, iX, iY);
    matrix.setBrightness(b);
    delay((iDuration / 2) / 16);
  }

}


void DrawValueFunction(int iValue, int iRightX, int iRightY, bool bWrite) {
  if (bDebug) {
    Serial.println("\n---Number Draw---");
    Serial.print("Initial Value: ");
    Serial.println(iValue);
  }
  iRightX = iRightX - 1;

  int iPlace = 1;

  if (iValue == 0)
    if (bWrite)
      DrawNum(0, iRightX, iRightY);
    else
      EraseNum(iRightX, iRightY);

  for (int i = 0; iPlace <= iValue; i++)
  {
    int iNum = (iValue / iPlace) % 10;
    if (bDebug) {
      Serial.print(iValue);
      Serial.print("/");
      Serial.print(iPlace);
      Serial.print("%10 = ");
      Serial.println(iNum);
    }
    if (bWrite)
      DrawNum(iNum, iRightX, iRightY);
    else
      EraseNum(iRightX, iRightY);
    iRightX -= 4;
    iPlace = iPlace * 10;
  }



}

void DrawValue(int iValue, int iRightX, int iRightY) {
  DrawValueFunction(iValue, iRightX, iRightY, bDraw);
}

void EraseValue(int iValue, int iRightX, int iRightY) {
  DrawValueFunction(iValue, iRightX, iRightY, !bDraw);
}


void DrawNum(int iNum, int iX, int iY) {
  switch (iNum) {
    case 0:
      matrix.drawFastVLine(iX, iY, 5, bDraw);
      matrix.drawPixel(iX + 1, iY, bDraw);
      matrix.drawFastVLine(iX + 2, iY, 5, bDraw);
      matrix.drawPixel(iX + 1, iY + 4, bDraw);
      break;
    case 1:
      matrix.drawFastVLine(iX + 1, iY, 5, bDraw);
      break;
    case 2:
      matrix.drawFastHLine(iX, iY, 3, bDraw);
      matrix.drawPixel(iX + 2, iY + 1, bDraw);
      matrix.drawFastHLine(iX, iY + 2, 3, bDraw);
      matrix.drawPixel(iX, iY + 3, bDraw);
      matrix.drawFastHLine(iX, iY + 4, 3, bDraw);
      break;
    case 3:
      matrix.drawFastHLine(iX, iY, 3, bDraw);
      matrix.drawPixel(iX + 2, iY + 1, bDraw);
      matrix.drawFastHLine(iX, iY + 2, 3, bDraw);
      matrix.drawPixel(iX + 2, iY + 3, bDraw);
      matrix.drawFastHLine(iX, iY + 4, 3, bDraw);
      break;
    case 4:
      matrix.drawFastVLine(iX, iY, 3, bDraw);
      matrix.drawPixel(iX + 1, iY + 2, bDraw);
      matrix.drawFastVLine(iX + 2, iY, 5, bDraw);
      break;
    case 5:
      matrix.drawFastHLine(iX, iY, 3, bDraw);
      matrix.drawPixel(iX, iY + 1, bDraw);
      matrix.drawFastHLine(iX, iY + 2, 3, bDraw);
      matrix.drawPixel(iX + 2, iY + 3, bDraw);
      matrix.drawFastHLine(iX, iY + 4, 3, bDraw);
      break;
    case 6:
      matrix.drawFastVLine(iX, iY, 5, bDraw);
      matrix.drawFastHLine(iX + 1, iY, 2, bDraw);
      matrix.drawFastHLine(iX + 1, iY + 2, 2, bDraw);
      matrix.drawPixel(iX + 2, iY + 3, bDraw);
      matrix.drawFastHLine(iX + 1, iY + 4, 2, bDraw);
      break;
    case 7:
      matrix.drawFastHLine(iX, iY, 2, bDraw);
      matrix.drawFastVLine(iX + 2, iY, 5, bDraw);
      break;
    case 8:
      matrix.drawFastVLine(iX, iY, 5, bDraw);
      matrix.drawPixel(iX + 1, iY, bDraw);
      matrix.drawPixel(iX + 1, iY + 2, bDraw);
      matrix.drawFastVLine(iX + 2, iY, 5, bDraw);
      matrix.drawPixel(iX + 1, iY + 4, bDraw);
      break;
    case 9:
      matrix.drawFastVLine(iX, iY, 3, bDraw);
      matrix.drawPixel(iX + 1, iY, bDraw);
      matrix.drawPixel(iX + 1, iY + 2, bDraw);
      matrix.drawFastVLine(iX + 2, iY, 5, bDraw);
      break;
    default:
      matrix.drawFastVLine(iX, iY, 2, bDraw);
      matrix.drawFastVLine(iX + 2, iY, 2, bDraw);
      matrix.drawPixel(iX + 1, iY + 2, bDraw);
      matrix.drawFastVLine(iX, iY + 3, 2, bDraw);
      matrix.drawFastVLine(iX + 2, iY + 3, 2, bDraw);
      break;
  }
}

void DrawPercent(int iX, int iY) {
  matrix.drawLine(iX, iY + 4, iX + 4, iY, bDraw);
  matrix.fillRect(iX, iY, 2, 2, bDraw);
  matrix.fillRect(iX + 3, iY + 3, 2, 2, bDraw);
}

void EraseNum(int iX, int iY) {
  matrix.fillRect(iX, iY, 3, 5, !bDraw);
}

void LED_clear() {
  if (bInvert)
    matrix.fillScreen();
  else
    matrix.clearScreen();
}

void setup() {
  Serial.begin(9600);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
  delay(100);
  LED_clear();

  if (bDebug)
    Serial.println("Begin Session~~");

  /*
    DrawLoadingBox();
    DrawPercent();
    matrix.writeScreen();

    DrawLoadZone(9);
    DrawValue(9,16,10);
    matrix.writeScreen();
    delay(1000);
  */

}


int gLoadLeft = 0;
int gLoadTop = 3;
int gBarWidth = 22;
int gBarHeight = 4;

void loop() {

  DrawLoadingBox(gLoadLeft, gLoadTop, gBarWidth+2, gBarHeight);
  DrawPercent(19, 10);
  DrawValue(0, 16, 10);
  matrix.writeScreen();


  for (int i = 0; i <= 100; i++)
  {
    EraseValue(i, 16, 10);
    DrawValue(i, 16, 10);
    //DrawLoadZone(i,gBarWidth,gBarHeight,gLoadLeft+1,gLoadTop+1);
    FlashLoadZone(i, gBarWidth, gBarHeight, gLoadLeft+1, gLoadTop+1, 800);

    matrix.writeScreen();
    //delay(2000);

  }


  delay(2000);
  LED_clear();

}
