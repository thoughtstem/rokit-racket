#include <CLCD.h>

void setup()
{
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)
}

void loop()
{
  // set the cursor to (0,0):
  CLCD.setCursor(0,0);
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) 
  {
   CLCD.print(thisChar);
   delay(500);
  }
  // set the cursor to (1,16):
  CLCD.setCursor(1,16);
   // set the display to automatically scroll:
  CLCD.autoscroll();
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) 
  {
      CLCD.print(thisChar);
      delay(500);
  }
  // turn off automatic scrolling  
  CLCD.noAutoscroll();
  // Display Clear
  CLCD.clearAll(); 
}



