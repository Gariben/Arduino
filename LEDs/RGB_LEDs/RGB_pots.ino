const bool bDebug = true;
const bool bStep = false;

#define COLORPOT 2
#define FREQPOT 3
#define RED 3
#define GREEN 5
#define BLUE 6

int iRed = 0;
int iGreen = 0;
int iBlue = 0;

void setup() {
if(bDebug){
  Serial.begin(9600);
  Serial.println("Debug mode! Serial messages will appear~~");
}
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
digitalWrite(RED, HIGH);
digitalWrite(GREEN, HIGH);
digitalWrite(BLUE, HIGH);
}

void loop() {
  GetRGBColor(analogRead(COLORPOT));
  GetTempo(analogRead(FREQPOT));

  if(bDebug && bStep)
    delay(1000);
}

void GetRGBColor(int iRead){
  iRead = iRead * 0.99609375;
  //0-765||255*3
  if(iRead < 255)
  {
    if(bDebug)
      Serial.println("RED/GREEN range");
    analogWrite(RED, iRead);
    analogWrite(GREEN, 255 - iRead);
    analogWrite(BLUE, 255);
    
  }
  else if(iRead >= 255 && iRead < 510)
  {
    if(bDebug)
      Serial.println("GREEN/BLUE range");
    analogWrite(GREEN, (iRead - 255));
    analogWrite(BLUE, 255 - (iRead - 255));
    analogWrite(RED, 255);
  }
  else if(iRead >=510 && iRead < 765)
  {
    if(bDebug)
      Serial.println("BLUE/RED range");
    analogWrite(BLUE, (iRead - 510));
    analogWrite(RED, 255 - (iRead - 510));
    analogWrite(GREEN, 255);

    
  }
  else
  {
    if(bDebug)
      Serial.println("RED/GREEN/BLUE range");
    analogWrite(BLUE, (iRead - 765));
    analogWrite(RED, (iRead - 765));
    analogWrite(GREEN, (iRead - 765));

  }

  if(bDebug)
  {
    Serial.print("Color Pot value: ");
    Serial.println(iRead);
  }
}

void GetTempo(int iRead)
{
  iRead = (iRead * 0.1173020527859) + 60;

  if(bDebug)
  {
    Serial.print("Freq Pot value: ");
    Serial.println(iRead);
    Serial.print("Delay time: ");
    Serial.println(60000/iRead);
  }

  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  delay(60000/iRead);


}

