/*** You must select MIDI from the "Tools > USB Type" menu ***/

//Serial Monitoring.
bool gDebug = false;

#include <TeensyThreads.h>
#include "rgb.h"

//Hardcoded Pins
#define PIN_WS2812B 2
#define PIN_POWER_LED 13
#define PIN_MIDI_LED 15


//SETUP
//-----------------------------------------------//

void setup()   {
  Buildrgb();
  if(gDebug){
    Serial.begin(115200);
    Serial.println("Booting Serial Monitor");
  }
  pinMode(PIN_POWER_LED, OUTPUT);
  pinMode(PIN_MIDI_LED, OUTPUT);

  digitalWrite(PIN_POWER_LED, HIGH);
  digitalWrite(PIN_MIDI_LED, LOW);
  threads.addThread(thread_LED);
}

//BEGIN GLOBAL FUNCTIONS
//-----------------------------------------------//

void GetNoteOctaveColor(int iNoteIn, int &iNoteOut, int &iOctaveOut, int &iColorOut){
  if(gDebug){
    Serial.println("\tGetNoteOctaveColor()");
    Serial.print("\tiNoteIn: ");
    Serial.println(iNoteIn, DEC);
  }
  int iDivisible = -1;
  iOctaveOut = 0;
  iOctaveOut = iNoteIn/12;
  if(gDebug){
    Serial.print("\tiOctaveOut: ");
    Serial.println(iOctaveOut, DEC);
  }
  for(iNoteOut=0; (iDivisible!=0)&&(iNoteOut<12); iNoteOut++)
   iDivisible = (iNoteIn-iNoteOut)%12;
  if(gDebug){
    Serial.print("\tiNoteOut: ");
    Serial.println(iNoteOut, DEC);
  }
  iNoteOut=iNoteOut-1;
  int CmajorNote=iNoteOut;

  //Get 0-6 from Cmajor Key
  constrain(CmajorNote,0,11);
  if(CmajorNote==0)iColorOut=1;
  if(CmajorNote==2)iColorOut=2; 
  if(CmajorNote==4)iColorOut=3; 
  if(CmajorNote==5)iColorOut=4; 
  if(CmajorNote==7)iColorOut=5; 
  if(CmajorNote==9)iColorOut=6; 
  if(CmajorNote==11)iColorOut=7;
  
  if(gDebug){
    Serial.print("\tiColorOut: ");
    Serial.println(iColorOut, DEC);
  }
}

void processMIDI(void) {
  byte byteType, byteChannel, byteNote, byteVelocity;
  int iNote, iOctave, iColor;

  byteType = usbMIDI.getType();       // which MIDI message, 128-255
  byteChannel = usbMIDI.getChannel(); // which MIDI channel, 1-16
  byteNote = usbMIDI.getData1();     // first data byte of message, 0-127
  byteVelocity = usbMIDI.getData2();     // second data byte of message, 0-127
  
  switch (byteType) {
    case usbMIDI.NoteOff: // 0x80
      digitalWrite(PIN_MIDI_LED, LOW);
      //LIGHTS_OFF();
      ErasePattern(((int)byteNote)/12);
      if(gDebug){
        Serial.print("NOTE OFF: ch=");
        Serial.print(byteChannel, DEC);
        Serial.print(", note_message=");
        Serial.print(byteNote, DEC);
        Serial.print(", velocity=");
        Serial.println(byteVelocity, DEC);
      }

      break;
    
    case usbMIDI.NoteOn: // 0x90
      digitalWrite(PIN_MIDI_LED, HIGH);
      GetNoteOctaveColor((int)byteNote,iNote,iOctave,iColor); 
      DisplayPattern(iColor,iOctave);    
      if(gDebug){
        Serial.print("NOTE ON: ch=");
        Serial.print(byteChannel, DEC);
        Serial.print(", note_message=");
        Serial.print(byteNote, DEC);
        Serial.print(", note_message=");
        Serial.print(byteNote, DEC);
        Serial.print(", velocity=");
        Serial.println(byteVelocity, DEC);
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
