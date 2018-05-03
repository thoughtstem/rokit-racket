#include <CLCD.h>

int InputSwitch = 15;

int cursor = 0;
int line = 1;

byte ArmsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

byte ArmsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

void setup()
{
  pinMode(InputSwitch, INPUT_PULLUP);
  
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)
  
  //make char maximam 8 (0 ~ 7)
  CLCD.makeCharacter(0, ArmsUp);
  CLCD.makeCharacter(1, ArmsDown);
  
  CLCD.setCursor(line,cursor);
  CLCD.write(0);
}

void loop()
{
  int sensorVal = digitalRead(InputSwitch);
  // push sensor => character move right  
  if (sensorVal != HIGH) 
  {
    if (cursor == 15)
    {
      if (line == 1) line = 2;
      else line = 1;
      cursor = 0;
    }
    else
    {
      cursor++; 
    }
    
    CLCD.clearAll();
    CLCD.setCursor(line,cursor);
    CLCD.write(0);
    delay(250);
    
    CLCD.clearAll();
    CLCD.setCursor(line,cursor);
    CLCD.write(1);
    delay(250);
    
   } 
}


