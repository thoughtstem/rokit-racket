#include <CLCD.h>

void setup()
{
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)

  CLCD.print("ARDU-X");
  CLCD.setCursor(2,0); // Second Line 0 position
  CLCD.print("Blink On Off");
}

void loop()
{
  // Blink cursor Off:
  CLCD.noBlink();
  delay(1000);
  // Blink cursor On:
  CLCD.blink();
  delay(1000);
}



