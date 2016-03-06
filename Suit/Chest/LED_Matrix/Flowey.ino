#include "Adafruit_GFX.h"
#include "Adafruit_HT1632.h"

const bool bDebug = false;
const bool bSit = false;
const bool bStep = false;
const bool bInvert = false;
int BPM = 1000;
const int iBrightness = 1;
const bool bDraw = !bInvert;

#define HT_DATA 2
#define HT_WR 3
#define HT_CS 4

Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);


class Flowey{
public:
  int m_iXOff;
  int m_iYOff;

  Flowey(){
    m_iXOff = 0;
    m_iYOff = 0;  
  }

  void OpenEyes(){
    matrix.drawFastVLine(7+m_iXOff, 2+m_iYOff, 5, bDraw);
    matrix.drawFastVLine(8+m_iXOff, 2+m_iYOff, 5, bDraw);
    matrix.drawFastVLine(15+m_iXOff, 2+m_iYOff, 5, bDraw);
    matrix.drawFastVLine(16+m_iXOff, 2+m_iYOff, 5, bDraw);
  }

  void PattyEyes(){
    matrix.drawFastVLine(7+m_iXOff, 2+m_iYOff, 3, bDraw);
    matrix.drawFastVLine(8+m_iXOff, 2+m_iYOff, 3, bDraw);
    matrix.drawFastHLine(6+m_iXOff, 5+m_iYOff, 4, bDraw);    
    matrix.drawFastVLine(15+m_iXOff, 2+m_iYOff, 3, bDraw);
    matrix.drawFastVLine(16+m_iXOff, 2+m_iYOff, 3, bDraw);
    matrix.drawFastHLine(14+m_iXOff, 5+m_iYOff, 4, bDraw); 
  }

  void WinkEyes(){
    matrix.drawFastVLine(7+m_iXOff, 2+m_iYOff, 5, bDraw);
    matrix.drawFastVLine(8+m_iXOff, 2+m_iYOff, 5, bDraw);
    matrix.drawFastHLine(14+m_iXOff, 5+m_iYOff, 4, bDraw);     
  }

  void SassEyes(){
    matrix.drawFastHLine(6+m_iXOff, 5+m_iYOff, 4, bDraw);
    matrix.drawFastHLine(7+m_iXOff, 6+m_iYOff, 2, bDraw);
    matrix.drawPixel(14+m_iXOff,2+m_iYOff,bDraw);
    matrix.drawPixel(15+m_iXOff,2+m_iYOff,bDraw);
    matrix.drawPixel(17+m_iXOff,3+m_iYOff,bDraw); 
    matrix.drawFastVLine(15+m_iXOff, 3+m_iYOff, 3, bDraw);
    matrix.drawFastVLine(16+m_iXOff, 3+m_iYOff, 3, bDraw);
    
  }
  
  void SketchEyes(){
    matrix.drawFastHLine(6+m_iXOff, 4+m_iYOff, 4, bDraw);
    matrix.drawFastVLine(7+m_iXOff, 5+m_iYOff, 2, bDraw);
    matrix.drawFastVLine(8+m_iXOff, 5+m_iYOff, 2, bDraw);
    matrix.drawFastHLine(14+m_iXOff, 4+m_iYOff, 4, bDraw);
    matrix.drawFastVLine(15+m_iXOff, 5+m_iYOff, 2, bDraw);
    matrix.drawFastVLine(16+m_iXOff, 5+m_iYOff, 2, bDraw);
  }

  void EraseEyes(){
    matrix.fillRect(6+m_iXOff, 2+m_iYOff, 4, 5, !bDraw);
    matrix.fillRect(14+m_iXOff, 2+m_iYOff, 4, 5, !bDraw);
    //matrix.writeScreen();   
  }
  
  void OpenMouth(){
    matrix.drawPixel(4+m_iXOff, 8+m_iYOff, bDraw);
    matrix.drawPixel(19+m_iXOff,8+m_iYOff, bDraw);
    matrix.drawFastHLine(5+m_iXOff, 9+m_iYOff, 14, bDraw);
    matrix.drawPixel(6+m_iXOff,10+m_iYOff, bDraw);
    matrix.drawPixel(17+m_iXOff,10+m_iYOff, bDraw);
    matrix.drawFastHLine(6+m_iXOff, 11+m_iYOff, 12, bDraw);
    matrix.drawFastHLine(7+m_iXOff, 12+m_iYOff, 10, bDraw);  
    matrix.drawFastHLine(8+m_iXOff, 13+m_iYOff, 8, bDraw);
  }

  void CloseMouth(){
    matrix.drawPixel(4+m_iXOff, 8+m_iYOff, bDraw);
    matrix.drawPixel(19+m_iXOff,8+m_iYOff, bDraw);
    matrix.drawFastHLine(5+m_iXOff, 9+m_iYOff, 14, bDraw);
    matrix.drawPixel(6+m_iXOff,10+m_iYOff, bDraw);
    matrix.drawPixel(17+m_iXOff,10+m_iYOff, bDraw);
    matrix.drawFastHLine(7+m_iXOff, 11+m_iYOff, 10, bDraw);
  }

  void TongueMouth(){
    matrix.drawPixel(4+m_iXOff, 8+m_iYOff, bDraw);
    matrix.drawPixel(19+m_iXOff,8+m_iYOff, bDraw);
    matrix.drawFastHLine(5+m_iXOff, 9+m_iYOff, 14, bDraw);
    matrix.drawFastVLine(6+m_iXOff, 10+m_iYOff, 2, bDraw);
    matrix.drawPixel(8+m_iXOff, 10+m_iYOff, bDraw);
    matrix.drawFastVLine(10+m_iXOff, 10+m_iYOff, 2, bDraw);
    matrix.drawFastHLine(7+m_iXOff, 12+m_iYOff, 3, bDraw);
    
  }

  void EraseMouth(){
    matrix.fillRect(4+m_iXOff, 8+m_iYOff, 16, 6, !bDraw);
    //matrix.writeScreen();
  }


};

Flowey flowey;



void LED_clear(){
  if(bInvert)
    matrix.fillScreen();
  else
    matrix.clearScreen();
}

void setup() {
  Serial.begin(9600);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
  matrix.setBrightness(iBrightness);
  delay(100);
  LED_clear();
  BPM = 60000/BPM;

  if(bDebug)
    Serial.println("Begin Session~~");


}

void loop() {

  int iDelayTime = 250;

  flowey.EraseEyes();
  flowey.EraseMouth();

  flowey.WinkEyes();
  flowey.TongueMouth();
  matrix.writeScreen();

  delay(iDelayTime * 8);

  flowey.EraseEyes();
  flowey.EraseMouth();
  
  for(int i=0; i<5; i++){
    flowey.OpenEyes();
    flowey.OpenMouth();
    matrix.writeScreen();
    delay(iDelayTime);

    flowey.EraseMouth();
    flowey.CloseMouth();
    matrix.writeScreen();
    delay(iDelayTime);
  }

  flowey.EraseEyes();
  for(int i=0; i<5; i++){
    flowey.SassEyes();
    flowey.OpenMouth();
    matrix.writeScreen();
    delay(iDelayTime);

    flowey.EraseMouth();
    flowey.CloseMouth();
    matrix.writeScreen();
    delay(iDelayTime);
    
  }

  flowey.EraseEyes();
  for(int i=0; i<5; i++){
    flowey.SketchEyes();
    flowey.OpenMouth();
    matrix.writeScreen();
    delay(iDelayTime);

    flowey.EraseMouth();
    flowey.CloseMouth();
    matrix.writeScreen();
    delay(iDelayTime);
  }

}
