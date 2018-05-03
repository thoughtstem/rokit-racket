#include <CLCD.h>

void setup()
{
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)
  CLCD.print("Time");
}

void loop()
{
  CLCD.setCursor(2,0);  // line 2, position 0
  CLCD.print(millis()/1000);  // 1 second Counte
}
