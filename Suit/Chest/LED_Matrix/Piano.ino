#include "Adafruit_GFX.h"
#include "Adafruit_HT1632.h"

const bool bDebug = false;
const bool bSit = false;
const bool bStep = false;
const bool bInvert = true;
int BPM = 500;
const int iKeyboardSize = 27;
const int iBrightness = 4;


struct Key{
  Key(int iIndex, bool bAcc){
    m_iIndex = iIndex;
    m_bAccidental = bAcc;
  }

  void Dec(){
    if(m_iIndex == 0)
      m_iIndex = iKeyboardSize;
    else
      m_iIndex--;
  }
  
  int m_iIndex;
  bool m_bAccidental;
};

#define HT_DATA 2
#define HT_WR 3
#define HT_CS 4

Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);

Key C(0,false);
  Key Db(4,true);
Key D(4,false);
  Key Eb(8,true);
Key E(8,false);
Key f(12,false);    //F is a macro lol
  Key Gb(16,true);
Key G(16,false);
  Key Ab(20,true);
Key A(20,false);
  Key Bb(24,true);
Key B(24,false);

bool OnRange(int iIndex){
  if(iIndex >=0 && iIndex <= matrix.width())
    return true;
  else
    return false;
}

void SetKey(Key kKey);
void SetKey(Key kKey){
  if(bDebug)
    Serial.println("\tSet Key:");
  if(!kKey.m_bAccidental)
  {  
    if(bDebug)
      Serial.println("\t\tNatural:");
    if(OnRange(kKey.m_iIndex))
      for(int j = 0; j < matrix.height(); j++)
          matrix.setPixel(kKey.m_iIndex,j);
  }
  else
  {
   if(bDebug)
    Serial.println("\t\tAccidental:");
    int iStart;
    int iEnd;
    switch(kKey.m_iIndex){
      case 0:
        iStart=0;
        iEnd=1;
        break;
       case iKeyboardSize:
        
        iStart=iKeyboardSize-1;
        iEnd=iKeyboardSize;
        break;
       default:
        iStart = kKey.m_iIndex -1;
        iEnd = kKey.m_iIndex+1;

        break;
    }
    if(bDebug){
      Serial.println(iStart);
      Serial.println(iEnd);    
    }

    if(OnRange(kKey.m_iIndex))
      for(int i = iStart; i <= iEnd; i++)
        for(int j = 0; j < 8; j++)
          matrix.setPixel(i,j);

    if(iStart==(iKeyboardSize-1))
      for(int j = 0; j < 8; j++)
        matrix.setPixel(0,j);
    }

}

void setup() {
  Serial.begin(9600);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
  matrix.setBrightness(iBrightness);
  delay(100);
  matrix.clearScreen();
  BPM = 60000/BPM;

  if(bDebug)
    Serial.println("Begin Session~~");
}

void loop() {

  SetKey(C);
    SetKey(Db);
  SetKey(D);
    SetKey(Eb);
  SetKey(E);
  SetKey(f);
    SetKey(Gb);
  SetKey(G);
    SetKey(Ab);
  SetKey(A);
    SetKey(Bb);
  SetKey(B);
  matrix.writeScreen();
  matrix.invertDisplay(bInvert);
  delay(BPM/4);
  if(!bSit){
    C.Dec();
      Db.Dec();
    D.Dec();
      Eb.Dec();
    E.Dec();
    f.Dec();
      Gb.Dec();
    G.Dec();
      Ab.Dec();
    A.Dec();
      Bb.Dec();
    B.Dec();
  
    if(bStep)
      delay(1000);
    
  
    matrix.clearScreen();
  }

}






