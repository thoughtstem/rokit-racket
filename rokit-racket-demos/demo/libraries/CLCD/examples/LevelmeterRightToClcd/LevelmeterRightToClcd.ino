#include <CLCD.h>

int levelAH = 0;
int levelAL = 0;

int levelBH = 0;
int levelBL = 0;

byte Level0[8] = {
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b00000
};

byte Level1[8] = {
  0b11111,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b11111,
  0b00000
};
 
byte Level2[8] = {
  0b11111,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11111,
  0b00000
};

byte Level3[8] = {
  0b11111,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11111,
  0b00000
};

byte Level4[8] = {
  0b11111,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11111,
  0b00000
};
 
byte Level5[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000
};

byte AlphabetL[8] = {
  0b11111,
  0b10111,
  0b10111,
  0b10111,
  0b10111,
  0b10001,
  0b11111,
  0b00000  
};

byte AlphabetR[8] = {
  0b11111,
  0b10001,
  0b10101,
  0b10011,
  0b10101,
  0b10101,
  0b11111,
  0b00000
};
     
void setup()
{
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)
  
  //make char maximam 8 (0 ~ 7)
  CLCD.makeCharacter(0,Level0);
  CLCD.makeCharacter(1,Level1);
  CLCD.makeCharacter(2,Level2);
  CLCD.makeCharacter(3,Level3);
  CLCD.makeCharacter(4,Level4);
  CLCD.makeCharacter(5,Level5);
  CLCD.makeCharacter(6,AlphabetL);  //L
  CLCD.makeCharacter(7,AlphabetR);  //R 
  
  CLCD.setCursor(1,0);

}

void loop()
{
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
   
  levelAH = sensorValue0/100;
  levelAL = sensorValue0%100;
  levelAL = levelAL/20;
  
  levelBH = sensorValue1/100;
  levelBL = sensorValue1%100;
  levelBL = levelBL/20;  
  
  //Line1 Display
  CLCD.setCursor(1,0);
  CLCD.write(6);
  for (int i = 0 ; i < levelAH ; i++) CLCD.write(5);
  CLCD.write(levelAL);
  for (int i = 0 ; i < 13-levelAH ; i++) CLCD.write(0);
  CLCD.write(0x5d);
  
  //Line2 Display
  CLCD.setCursor(2,0);
  CLCD.write(7);
  for (int i = 0 ; i < levelBH ; i++) CLCD.write(5);
  CLCD.write(levelBL);
  for (int i = 0 ; i < 13-levelBH ; i++) CLCD.write(0);
  CLCD.write(0x5d);
  
}


