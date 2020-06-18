#include <WS2812Serial.h>

bool gEnableLogging = false;

const int pin = 1;

// Usable pins:
//   Teensy LC:   1, 4, 5, 24
//   Teensy 3.2:  1, 5, 8, 10, 31   (overclock to 120 MHz for pin 8)
//   Teensy 3.5:  1, 5, 8, 10, 26, 32, 33, 48
//   Teensy 3.6:  1, 5, 8, 10, 26, 32, 33
//   Teensy 4.0:  1, 8, 14, 17, 20, 24, 29, 39

#define BLANK  0x000000
#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF

int Rainbow[8];
const int numled = 150;
int strips=10;
int len=15;
int iColor=BLANK;

byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

void setup() {

  //Monitoring
  if(gEnableLogging){
    Serial.begin(115200);
    Serial.println("Booting Serial Monitor");
  }

  //Colors
  Rainbow[0] = BLANK;
  Rainbow[1] = RED;
  Rainbow[2] = ORANGE;
  Rainbow[3] = YELLOW;
  Rainbow[4] = GREEN;
  Rainbow[5] = BLUE;
  Rainbow[6] = PINK;
  Rainbow[7] = WHITE;

  //LED Strip init
  leds.begin();
  for (int i=0; i < numled; i+=15) {
    for(int j=0; j<strips; j++){ 
      leds.setPixel((i+j), BLANK);
      leds.setPixel((numled-1)-(i+j), BLANK);
    }
    leds.show();
  } 
}

void loop() {
    if(usbMIDI.read()){
      if(usbMIDI.getType() == usbMIDI.NoteOff){
        iColor=Rainbow[0];
        if(gEnableLogging)
          Serial.println("NOTE OFF");
      }else if(usbMIDI.getType() == usbMIDI.NoteOn){
        (((usbMIDI.getData1()%12)+1) > 7) ? iColor=Rainbow[0] : iColor=Rainbow[(usbMIDI.getData1()%12)+1];
        if(gEnableLogging)
        {
          Serial.print("NOTE ON: ");
          Serial.print(usbMIDI.getData1());
          Serial.print("->");
          Serial.println((usbMIDI.getData1()%12)+1);
        }
      }
      
      for (int i=0; i < numled; i+=15) {
        for(int j=0; j<strips; j++){ 
          leds.setPixel((i+j), iColor);
          leds.setPixel((numled-1)-(i+j), iColor);
        }
      }
      leds.show();
   }
}
