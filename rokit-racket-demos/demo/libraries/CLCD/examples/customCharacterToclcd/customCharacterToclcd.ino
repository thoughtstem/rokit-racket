#include <CLCD.h>

byte Arrow0[8] = {
  0b00000,
  0b001111,
  0b000011,
  0b000101,
  0b001001,
  0b010000,
  0b100000,
  0b000000
};
 
byte Arrow1[8] = {
  0b00000,
  0b11110,
  0b11000,
  0b10100,
  0b10010,
  0b00001,
  0b00000,
  0b00000
};

byte Arrow2[8] = {
   0b00000,
   0b00000,
   0b10000,
   0b01001,
   0b00101,
   0b00011,
   0b01111,
   0b00000
};

byte Arrow3[8] = {
  0b00000,
  0b00000,
  0b00001,
  0b10010,
  0b10100,
  0b11000,
  0b11110,
  0b00000
};
 
byte Heart[8] = {
  0b00000,
  0b01010,
  0b10101,
  0b10001,
  0b10001,
  0b01010,
  0b00100,
  0b00000
};

byte HeartInvert[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b01110,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

byte Smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte Frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};
     
void setup()
{
  
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)
  
  //make char maximam 8 (0 ~ 7)
  CLCD.makeCharacter(0,Arrow0);
  CLCD.makeCharacter(1,Arrow1);
  CLCD.makeCharacter(2,Arrow2);
  CLCD.makeCharacter(3,Arrow3);
  CLCD.makeCharacter(4,Heart);
  CLCD.makeCharacter(5,HeartInvert);
  CLCD.makeCharacter(6,Smiley);  
  CLCD.makeCharacter(7,Frownie);  
  
  CLCD.setCursor(1,0);  // First Line 0 Position
  CLCD.write(0);
  CLCD.write(1);
  CLCD.write(2);
  CLCD.write(3);
  CLCD.write(4);
  CLCD.write(5);
  CLCD.write(6);
  CLCD.write(7);
  
}

void loop()
{
 
}


