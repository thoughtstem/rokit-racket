#include <CLCD.h>

void setup()
{
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)

  CLCD.print("HUNOI for ");
  CLCD.setCursor(2,9); // Second Line 8 position
  CLCD.print("Arduino");
}

void loop()
{
  for(int i = 0; i <= 45; i ++)
  { 
    if(i < 15) CLCD.scrollLeft(); // Left Shift
    else  CLCD.scrollRight();     // Right Shift
    delay(250);
  }
}



