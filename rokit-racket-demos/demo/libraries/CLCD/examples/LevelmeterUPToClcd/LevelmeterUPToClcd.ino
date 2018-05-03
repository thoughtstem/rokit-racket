#include <CLCD.h>

#define  Level0  0x20;

int level = 0;
int position = 0;

byte Level1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};
 
byte Level2[8] = {
 0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111
};

byte Level3[8] = {
 0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111
};

byte Level4[8] = {
 0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
 
byte Level5[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte Level6[8] = {
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte Level7[8] = {
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte Level8[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
     
void setup()
{
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)
  
  //make char maximam 8 (0 ~ 7)
  CLCD.makeCharacter(0,Level1);
  CLCD.makeCharacter(1,Level2);
  CLCD.makeCharacter(2,Level3);
  CLCD.makeCharacter(3,Level4);
  CLCD.makeCharacter(4,Level5);
  CLCD.makeCharacter(5,Level6);
  CLCD.makeCharacter(6,Level7);  
  CLCD.makeCharacter(7,Level8);  
  
  CLCD.setCursor(1,0);

}

void loop()
{
  int sensorValue = analogRead(A0);

  level = map(sensorValue, 100, 1023, 0, 7);  
  if (sensorValue < 100) level = Level0;
  
  CLCD.setCursor(1,position);
  for (int i = 0 ; i < 15 ; i++) CLCD.write(level);
  
  position = position + 1;
  if (position == 16) position = 0;
  
  CLCD.setCursor(2,0);
  CLCD.print(sensorValue);
  CLCD.write(0x20);  // clear for 4th number 
}


