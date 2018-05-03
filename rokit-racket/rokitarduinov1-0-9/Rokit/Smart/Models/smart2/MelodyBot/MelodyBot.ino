/*****************************
//MelodyBot Example
//2015-06-04 RoboLink
******************************/
#include <SmartInventor.h>

#define PUSHED  0x00

int note = 0;
unsigned char ledSignal = 0;
int melody[] = {
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4 };
byte sevenLed[] = {
  0b11111111, 0b01111111, 0b00111111, 0b00011111, 0b00001111, 0b00000111, 0b00000011, 0b00000001};
unsigned int sum = 0, mean = 0;

int minSen = 1023;
int maxSen = 0;
int performance = 0;

void setup()
{
  Serial.begin(57600);

  pinMode(23,INPUT_PULLUP);
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
    pinMode(thisPin, OUTPUT);  
  } 
  SmartInventor.LedArray(0);
}

void loop()
{
  int bt = digitalRead(23);
  int sen = analogRead(22);

  minSen = min(sen,minSen);
  maxSen = max(sen,maxSen);

  note = map(sen, minSen, maxSen, 0, 8);

if(note > 7) note = 7;
  if((maxSen - minSen) > 50) performance = 1;

Serial.println(note);

  if(performance == 1)
  {
    SmartInventor.LedArray(sevenLed[note]);
    if(bt == PUSHED) tone(7, melody[note], 100);
  }
}




