/*** You must select MIDI from the "Tools > USB Type" menu ***/

//Serial Monitoring.
bool gDebug = false;

#include "rgb.h"

//Hardcoded Pins
#define PIN_WS2812B 2
#define PIN_RED 3
#define PIN_GREEN 4
#define PIN_BLUE 5
#define PIN_POWER_LED 13
#define PIN_MIDI_LED 14



//SETUP
//-----------------------------------------------//

void setup()   {
  Buildrgb();
  if(gDebug){
    Serial.begin(115200);
    Serial.println("Booting Serial Monitor");
  }
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_POWER_LED, OUTPUT);
  pinMode(PIN_MIDI_LED, OUTPUT);

  digitalWrite(PIN_POWER_LED, HIGH);
  digitalWrite(PIN_MIDI_LED, LOW);
}

//BEGIN GLOBAL FUNCTIONS
//-----------------------------------------------//

int GetNoteOfOctave(int iNoteIn){
  int iDivisible = -1;
  int iNoteOut = 0;
  for(iNoteOut=0; (iDivisible!=0)&&(iNoteOut<12); iNoteOut++)
    iDivisible = (iNoteIn-iNoteOut)%12;
  return (iNoteOut-1);
}

int GetCMajorDegree(int iNoteIn){
  //This is sloppy, don't show my mommy.
  int iNoteOut=-1; //default to off.
  if(iNoteIn==0)iNoteOut=0;
  if(iNoteIn==2)iNoteOut=1; 
  if(iNoteIn==4)iNoteOut=2; 
  if(iNoteIn==5)iNoteOut=3; 
  if(iNoteIn==7)iNoteOut=4; 
  if(iNoteIn==9)iNoteOut=5; 
  if(iNoteIn==11)iNoteOut=6; 
  return iNoteOut+1; 
}

void processMIDI(void) {
  byte byteType, byteChannel, byteNote, byteVelocity;
  int iNote, iMajorDegree, iBrightness;

  byteType = usbMIDI.getType();       // which MIDI message, 128-255
  byteChannel = usbMIDI.getChannel(); // which MIDI channel, 1-16
  byteNote = usbMIDI.getData1();     // first data byte of message, 0-127
  byteVelocity = usbMIDI.getData2();     // second data byte of message, 0-127
  
  switch (byteType) {
    case usbMIDI.NoteOff: // 0x80
      iNote = GetNoteOfOctave((int)byteNote);
      digitalWrite(PIN_MIDI_LED, LOW);
      LIGHTS_OFF();
      if(gDebug){
        Serial.print("NOTE OFF: ch=");
        Serial.print(byteChannel, DEC);
        Serial.print(", note_message=");
        Serial.print(byteNote, DEC);
        Serial.print(", note=");
        Serial.print(iNote, DEC);
        Serial.print(", velocity=");
        Serial.println(byteVelocity, DEC);
      }

      break;
    
    case usbMIDI.NoteOn: // 0x90
      iNote = GetNoteOfOctave((int)byteNote);
      digitalWrite(PIN_MIDI_LED, HIGH);
      iMajorDegree=GetCMajorDegree(iNote);
      iBrightness = (int)(float(byteVelocity)*((float)100.0 / (float)128.0));
      LIGHTS_ON(iMajorDegree, iBrightness);      
      if(gDebug){
        Serial.print("NOTE ON: ch=");
        Serial.print(byteChannel, DEC);
        Serial.print(", note_message=");
        Serial.print(byteNote, DEC);
        Serial.print(", note=");
        Serial.print(iNote, DEC);     
        Serial.print(", color=");
        Serial.print(iMajorDegree, DEC); 
        Serial.print(", velocity=");
        Serial.print(byteVelocity, DEC);
        Serial.print(", brightness=");
        Serial.println(iBrightness, DEC);
      }
      break;
    
    default:
      if(gDebug){
        Serial.println("WARNING: Unknown Message Received.");
      }
  }
}


//BEGIN LOOP
//-----------------------------------------------//

void loop()                     
{
  if (usbMIDI.read()) {
    processMIDI();
  }
}
