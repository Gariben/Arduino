#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#define PIN 4

#define NEXT 10
#define BACK 9
#define CYCLE 14
#define SPECIAL1 12
#define SPECIAL2 11
const int gSize = 16;
int8_t gState = 0;
int8_t gCycle = 0;
bool bChange = false;
bool bTempAnimation=false;

int m_iCityLites[8];

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
Adafruit_NeoPixel ring = Adafruit_NeoPixel(32, PIN);

void AnimationIntro(int iState)
{
  switch(iState){

    case 0:
      //"Off" position
      break;
    case 1:
      //"City of Tiny Lites" animation intro
      for (int i = 0; i <= (gSize / 2); i += 2) {
        ring.setPixelColor(8 - i, ring.Color(255, 255, 0));
        if (i < 8)ring.setPixelColor(8 + i, ring.Color(255, 255, 0));
        ring.show();
        delay(100);
      }

      matrix.setTextSize(1);
      matrix.setTextWrap(false); 
      for (int8_t x=0; x>=-101; x--) {
        matrix.clear();
        matrix.setCursor(x,0);
        matrix.print("City of Tiny Lites");
        matrix.writeDisplay();
        delay(30);
      }

      break;
    case 2:
      //"Heroes" animation intro
      for (int i = 0; i <= (gSize / 2); i++) {
        ring.setPixelColor(8 - i, ring.Color(255, 255, 255));
        if (i < 8)ring.setPixelColor(8 + i, ring.Color(255, 255, 255));
        ring.show();
        delay(100);
      }

      matrix.setTextSize(1);
      matrix.setTextWrap(false); 
      for (int8_t x=7; x>=-36; x--) {
        matrix.clear();
        matrix.setCursor(x,0);
        matrix.print("Heroes");
        matrix.writeDisplay();
        delay(30);
      }
      break;
    case 3:
      //"Frame by Frame" animation intro
      for (int i = 15; i >= 0; i--) {
        ring.setPixelColor(i, ring.Color(255, 0, 0));
        ring.show();
        delay(100);
      }
      matrix.setTextSize(1);
      matrix.setTextWrap(false); 
      for (int8_t x=0; x>=-36; x--) {
        matrix.clear();
        matrix.setCursor(x,0);
        matrix.print("Frame");
        matrix.writeDisplay();
        delay(40);
      }

      matrix.setRotation(1);
      for (int8_t x=7; x>=-36; x--) {
        matrix.clear();
        matrix.setCursor(x,0);
        matrix.print("By");
        matrix.writeDisplay();
        delay(40);
      }

      matrix.setRotation(3);
      for (int8_t x=7; x>=-36; x--) {
        matrix.clear();
        matrix.setCursor(x,0);
        matrix.print("Frame");
        matrix.writeDisplay();
        delay(40);
      }
      matrix.setRotation(0);
      break;
  }
}


void AnimationLoop(int iState, int iCycle)
{

  switch(iState){

    case 0:
      //"Off" position
      break;
    case 1:
      //"City of Tiny Lites" animation loop
      switch(iCycle){

        case 0:
          for (int i = 0; i < 16; i++) {
            if(i>=4){
              ring.setPixelColor(i, ring.Color(255, 255, 0));
              ring.setPixelColor(i-1, ring.Color(255, 255, 0));
              ring.setPixelColor(i-2, ring.Color(255, 255, 0));
              ring.setPixelColor(i-3, ring.Color(255, 255, 0));
              ring.setPixelColor(i-4, ring.Color(0, 0, 0));              
            }else if(i==0){
              ring.setPixelColor(0, ring.Color(255, 255, 0));
              ring.setPixelColor(15, ring.Color(255, 255, 0));
              ring.setPixelColor(14, ring.Color(255, 255, 0));
              ring.setPixelColor(13, ring.Color(255, 255, 0));
              ring.setPixelColor(12, ring.Color(0, 0, 0));              
            }else if(i==1){
              ring.setPixelColor(1, ring.Color(255, 255, 0));
              ring.setPixelColor(0, ring.Color(255, 255, 0));
              ring.setPixelColor(15, ring.Color(255, 255, 0));
              ring.setPixelColor(14, ring.Color(255, 255, 0));
              ring.setPixelColor(13, ring.Color(0, 0, 0));              
            }else if(i==2){
              ring.setPixelColor(2, ring.Color(255, 255, 0));
              ring.setPixelColor(1, ring.Color(255, 255, 0));
              ring.setPixelColor(0, ring.Color(255, 255, 0));
              ring.setPixelColor(15, ring.Color(255, 255, 0));
              ring.setPixelColor(14, ring.Color(0, 0, 0));              
            }else if(i==3){
              ring.setPixelColor(3, ring.Color(255, 255, 0));
              ring.setPixelColor(2, ring.Color(255, 255, 0));
              ring.setPixelColor(1, ring.Color(255, 255, 0));
              ring.setPixelColor(0, ring.Color(255, 255, 0));
              ring.setPixelColor(15, ring.Color(0, 0, 0));              
            }

              
              matrix.clear();
              matrix.drawLine(6,0,6,1,LED_ON);
              matrix.drawLine(7,0,7,1,LED_ON);              
              for(int j = 0; j < 7; j++){
                m_iCityLites[j] = m_iCityLites[j+1];
                matrix.drawLine(j,7, j, m_iCityLites[j], LED_ON);
              }
              m_iCityLites[7]=random(3,8);
              matrix.drawLine(7,7,7,m_iCityLites[7],LED_ON);
              matrix.writeDisplay();
              ring.show();
              delay(50);
          }

          break;
        case 1:
          iCycle=0;
          break;
        case 2:
          iCycle=0;
          break;
      }

      break;
    case 2:
      //"Heroes" animation loop
      switch(iCycle){
        case 0:
         for (int i = 0; i < 16; i++) {
          
            if(i>=4){
              ring.setPixelColor(i, ring.Color(255, 255, 255));
              ring.setPixelColor(i-1, ring.Color(255, 255, 255));
              ring.setPixelColor(i-2, ring.Color(255, 255, 255));
              ring.setPixelColor(i-3, ring.Color(255, 255, 255));
              ring.setPixelColor(i-4, ring.Color(0, 0, 255));              
            }else if(i==0){
              ring.setPixelColor(0, ring.Color(255, 255, 255));
              ring.setPixelColor(15, ring.Color(255, 255, 255));
              ring.setPixelColor(14, ring.Color(255, 255, 255));
              ring.setPixelColor(13, ring.Color(255, 255, 255));
              ring.setPixelColor(12, ring.Color(0, 0, 255));              
            }else if(i==1){
              ring.setPixelColor(1, ring.Color(255, 255, 255));
              ring.setPixelColor(0, ring.Color(255, 255, 255));
              ring.setPixelColor(15, ring.Color(255, 255, 255));
              ring.setPixelColor(14, ring.Color(255, 255, 255));
              ring.setPixelColor(13, ring.Color(0, 0, 255));              
            }else if(i==2){
              ring.setPixelColor(2, ring.Color(255, 255, 255));
              ring.setPixelColor(1, ring.Color(255, 255, 255));
              ring.setPixelColor(0, ring.Color(255, 255, 255));
              ring.setPixelColor(15, ring.Color(255, 255, 255));
              ring.setPixelColor(14, ring.Color(0, 0, 255));              
            }else if(i==3){
              ring.setPixelColor(3, ring.Color(255, 255, 255));
              ring.setPixelColor(2, ring.Color(255, 255, 255));
              ring.setPixelColor(1, ring.Color(255, 255, 255));
              ring.setPixelColor(0, ring.Color(255, 255, 255));
              ring.setPixelColor(15, ring.Color(0, 0, 255));              
            }

            //Matrix routine
            if(i==0 && i<4){
              matrix.clear();
              matrix.drawLine(3,3,3,4,LED_ON);
              matrix.drawLine(4,3,4,4,LED_ON);
            }

            if(i==4 && i<8){
              matrix.clear();
              matrix.drawLine(3,2,4,2,LED_ON);
              matrix.drawLine(2,3,2,4,LED_ON);
              matrix.drawLine(3,5,4,5,LED_ON);
              matrix.drawLine(5,3,5,4,LED_ON);
            }

            if(i==8 && i<12){
              matrix.clear();
              matrix.drawLine(1,2,1,5,LED_ON);
              matrix.drawLine(6,2,6,5,LED_ON);
              matrix.drawLine(2,1,5,1,LED_ON);
              matrix.drawLine(2,6,5,6,LED_ON);  
              
            }
            

            if(i==12 && i<16){
              matrix.clear();
              matrix.drawLine(1,0,6,0,LED_ON);
              matrix.drawLine(1,7,6,7,LED_ON);
              matrix.drawLine(0,1,0,6,LED_ON);
              matrix.drawLine(7,1,7,6,LED_ON);
            }


            

              matrix.writeDisplay();
              ring.show();
              delay(75);
          }
        
          break;
        case 1:
          matrix.clear();
          matrix.setCursor(0,0);
          matrix.print("5");
          matrix.writeDisplay();
          for (int i = 0; i < 16; i++) {
            ring.setPixelColor(i, ring.Color(0, 190, 0));
          }
          ring.show();
          break;
        case 2:
          matrix.clear();
          matrix.setCursor(0,0);
          matrix.print("6");
          matrix.writeDisplay();
          for (int i = 0; i < 16; i++) {
            ring.setPixelColor(i, ring.Color(0, 130, 0));
          }
          ring.show();
          break;
      }
      break;
    case 3:
      //"Frame By Frame" animation loop
      switch(iCycle){

        case 0:
          for (int i = 0; i < 16; i++) {
            if(i>=4){
              ring.setPixelColor(i, ring.Color(255, 0, 0));
              ring.setPixelColor(i-1, ring.Color(255, 0, 0));
              ring.setPixelColor(i-2, ring.Color(255, 0, 0));
              ring.setPixelColor(i-3, ring.Color(255, 0, 0));
              ring.setPixelColor(i-4, ring.Color(0, 0, 0));


            }else if(i==0){
              ring.setPixelColor(0, ring.Color(255, 0, 0));
              ring.setPixelColor(15, ring.Color(255, 0, 0));
              ring.setPixelColor(14, ring.Color(255, 0, 0));
              ring.setPixelColor(13, ring.Color(255, 0, 0));
              ring.setPixelColor(12, ring.Color(0, 0, 0));         

            }else if(i==1){
              ring.setPixelColor(1, ring.Color(255, 0, 0));
              ring.setPixelColor(0, ring.Color(255, 0, 0));
              ring.setPixelColor(15, ring.Color(255, 0, 0));
              ring.setPixelColor(14, ring.Color(255, 0, 0));
              ring.setPixelColor(13, ring.Color(0, 0, 0));              
            }else if(i==2){
              ring.setPixelColor(2, ring.Color(255, 0, 0));
              ring.setPixelColor(1, ring.Color(255, 0, 0));
              ring.setPixelColor(0, ring.Color(255, 0, 0));
              ring.setPixelColor(15, ring.Color(255, 0, 0));
              ring.setPixelColor(14, ring.Color(0, 0, 0));              
            }else if(i==3){
              ring.setPixelColor(3, ring.Color(255, 0, 0));
              ring.setPixelColor(2, ring.Color(255, 0, 0));
              ring.setPixelColor(1, ring.Color(255, 0, 0));
              ring.setPixelColor(0, ring.Color(255, 0, 0));
              ring.setPixelColor(15, ring.Color(0, 0, 0));              
            }              
              
              
            if(i<=8){
              ring.setPixelColor(8-i, ring.Color(255,255,255));
              ring.setPixelColor((8-i)+1, ring.Color(255,255,255));
              ring.setPixelColor((8-i)+2, ring.Color(255,255,255));
              ring.setPixelColor((8-i)+3, ring.Color(255,255,255));
              ring.setPixelColor((8-i)+4, ring.Color(0,0,0));
            }

            if(i==9){
              ring.setPixelColor(15, ring.Color(255,255,255));
              ring.setPixelColor(0, ring.Color(255,255,255));
              ring.setPixelColor(1, ring.Color(255,255,255));
              ring.setPixelColor(2, ring.Color(255,255,255));
              ring.setPixelColor(3, ring.Color(0,0,0));  
            }
              
            if(i==10){
              ring.setPixelColor(14, ring.Color(255,255,255));
              ring.setPixelColor(15, ring.Color(255,255,255));
              ring.setPixelColor(0, ring.Color(255,255,255));
              ring.setPixelColor(1, ring.Color(255,255,255));
              ring.setPixelColor(2, ring.Color(0,0,0));  
            }              
              
            if(i==11){
              ring.setPixelColor(13, ring.Color(255,255,255));
              ring.setPixelColor(14, ring.Color(255,255,255));
              ring.setPixelColor(15, ring.Color(255,255,255));
              ring.setPixelColor(0, ring.Color(255,255,255));
              ring.setPixelColor(1, ring.Color(0,0,0));   
            }    

            if(i==12){
              ring.setPixelColor(12, ring.Color(255,255,255));
              ring.setPixelColor(13, ring.Color(255,255,255));
              ring.setPixelColor(14, ring.Color(255,255,255));
              ring.setPixelColor(15, ring.Color(255,255,255));
              ring.setPixelColor(0, ring.Color(0,0,0));  
            }

            if(i > 12 && i < 16){
              ring.setPixelColor((24-i), ring.Color(255,255,255));
              ring.setPixelColor((24-i)+1, ring.Color(255,255,255));
              ring.setPixelColor((24-i)+2, ring.Color(255,255,255));
              ring.setPixelColor((24-i)+3, ring.Color(255,255,255));
              ring.setPixelColor((24-i)+4, ring.Color(0,0,0));  


              
            }
              matrix.clear();
              int iValue = i;
              if((i>=0 && i<=4) || (i>=8 && i<=12)){
                iValue = ((i > 8) ? i-8 : i);
                matrix.fillRect(iValue,0, 4,4, LED_ON);
                matrix.fillRect(4-iValue,4,4,4, LED_ON);
              } 
              if((i>=4 && i<=8) || (i>=12 && i<=15)){
                iValue = ((i > 8) ? i-8 : i);
                matrix.fillRect(4,iValue-4, 4,4, LED_ON);
                matrix.fillRect(0,8-iValue,4,4, LED_ON);
              }    
              matrix.writeDisplay();
              ring.show();
              delay(100);
          }
          break;
        case 1:
          matrix.clear();
          matrix.setCursor(0,0);
          matrix.print("8");
          matrix.writeDisplay();
          for (int i = 0; i < 16; i++) {
            ring.setPixelColor(i, ring.Color(0, 0, 190));
          }
          ring.show();
          break;
        case 2:
          matrix.clear();
          matrix.setCursor(0,0);
          matrix.print("9");
          matrix.writeDisplay();
          for (int i = 0; i < 16; i++) {
            ring.setPixelColor(i, ring.Color(0, 0, 130));
          }
          ring.show();
          break;
      }
      break;
  }
  if(bTempAnimation)
    bTempAnimation=false;
}

void SpecialAnimation1(int iState, int iCycle){
  switch(iState){

    case 0:
      break;
    case 1:
      switch(iCycle){

        case 0:
          for (int i = 1; i < 16; i++) {
            ring.setPixelColor(i, ring.Color(255, 0, 0));
            ring.setPixelColor(i-1, ring.Color(0, 0, 0));
            delay(100);
            ring.show();           
          }

          break;
        case 1:
          break;
        case 2:
          break;
      }

      break;
    case 2:
      switch(iCycle){

        case 0:
          break;
        case 1:
          break;
        case 2:
          break;
      }
      break;
    case 3:
      switch(iCycle){

        case 0:
          break;
        case 1:
          break;
        case 2:
          break;
      }
      break;
  }

}

void SpecialAnimation2(int iState, int iCycle){
  switch(iState){

    case 0:
      break;
    case 1:
      switch(iCycle){

        case 0:
          for (int i = 14; i > 0; i--) {
            ring.setPixelColor(i, ring.Color(255, 0, 0));
            ring.setPixelColor(i+1, ring.Color(0, 0, 0));
            delay(100);
            ring.show();           
          }

          break;
        case 1:
          break;
        case 2:
          break;
      }

      break;
    case 2:
      switch(iCycle){

        case 0:
          break;
        case 1:
          break;
        case 2:
          break;
      }
      break;
    case 3:
      switch(iCycle){

        case 0:
          break;
        case 1:
          break;
        case 2:
          break;
      }
      break;
  }

}

void NextAnimationCycle(int iState, int iCycle)
{
  switch(iState){
    case 0:

      break;
    case 1:
      if(gCycle<2)
        gCycle++;
      else
        gCycle=0;
      break;
   case 2:
      if(gCycle<2)
        gCycle++;
      else
        gCycle=0;
      break;
   case 3:
      if(gCycle<2)
        gCycle++;
      else
        gCycle=0;
      break;   
  }
  
}

bool Pressed(int iPin)
{
  int iState = 0;
  iState = digitalRead(iPin);
  if (iState == HIGH)
    return true;
  else
    return false; 
}

void Wipe(){

  matrix.clear();
  matrix.writeDisplay();
  for(int i=0; i<16; i++){
    ring.setPixelColor(i,0);
  }

  ring.show();

  
}


void setup() {
#ifdef __AVR_ATtiny85__
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  ring.begin();
  ring.setBrightness(85); // 1/3 brightness

  matrix.begin(0x70);  // pass in the address

  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);

  for(int i=0; i<8; i++)
    m_iCityLites[i] = i;

  matrix.clear();      // clear display
  matrix.drawPixel(6, 0, LED_ON);
  matrix.drawPixel(7, 0, LED_ON);
  matrix.drawPixel(7, 1, LED_ON);

  matrix.drawPixel(1, 2, LED_ON);
  matrix.drawPixel(1, 3, LED_ON);
  matrix.drawPixel(2, 4, LED_ON);
  matrix.drawPixel(3, 2, LED_ON);
  matrix.drawPixel(3, 3, LED_ON);

  matrix.drawPixel(4, 4, LED_ON);
  matrix.drawPixel(4, 5, LED_ON);
  matrix.drawPixel(5, 6, LED_ON);
  matrix.drawPixel(6, 4, LED_ON);
  matrix.drawPixel(6, 5, LED_ON);

  matrix.drawPixel(0, 6, LED_ON);
  matrix.drawPixel(0, 7, LED_ON);
  matrix.drawPixel(1, 7, LED_ON);  
  matrix.writeDisplay();

  for (int i = 0; i <= (gSize / 2); i += 1) {
    ring.setPixelColor(8 - i, ring.Color(255, 0, 0));
    if (i < 8)ring.setPixelColor(8 + i, ring.Color(255, 0, 0));
    ring.show();
    delay(100);
  }
  delay(1000);


  matrix.clear();
  matrix.writeDisplay();

  for (int i = 0; i <= (gSize / 2); i += 1) {
    ring.setPixelColor(8 - i, ring.Color(0, 0, 0));
    if (i < 8)ring.setPixelColor(8 + i, ring.Color(0, 0, 0));
    ring.show();
  }


}

void loop() {
  if(bChange)
  {
    AnimationIntro(gState);
    bChange = false;
  }


  if(Pressed(NEXT))
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(1000);

    Wipe();
    
    if(gState<3)
      gState++;
    else
      gState=0;

    gCycle=0;
    bChange = true;
  }else if(Pressed(BACK))
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(1000);    

    Wipe();
    
    if(gState>0)
      gState--;
    else
      gState=2;

    gCycle=0;
    bChange = true;
  }else
  {
    AnimationLoop(gState, gCycle);
  }

  if(Pressed(CYCLE))
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(1000); 
    NextAnimationCycle(gState, gCycle);
    
  }else if(Pressed(SPECIAL1))
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(1000); 
    SpecialAnimation1(gState, gCycle);
    bTempAnimation=true;
  }else if(Pressed(SPECIAL2))
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(1000); 
    SpecialAnimation2(gState, gCycle);
    bTempAnimation=true;   
  }else if(Pressed(NEXT))
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(1000);

    Wipe();
    
    if(gState<3)
      gState++;
    else
      gState=0;

    gCycle=0;
    bChange = true;
  }else if(Pressed(BACK))
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(1000);    

    Wipe();
    
    if(gState>0)
      gState--;
    else
      gState=2;

    gCycle=0;
    bChange = true;
  }  

}
