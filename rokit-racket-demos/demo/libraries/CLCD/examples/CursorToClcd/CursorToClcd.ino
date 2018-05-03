#include <CLCD.h>

void setup()
{
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)

  CLCD.print("ARDU-X");
  CLCD.setCursor(2,0); // Second Line 0 position
  CLCD.print("Cursor On Off");
}

void loop()
{
  // Turn off the Cursor:
  CLCD.noCursor();
  delay(500);
  // Turn on the Cursor:
  CLCD.cursor();
  delay(500);
}



