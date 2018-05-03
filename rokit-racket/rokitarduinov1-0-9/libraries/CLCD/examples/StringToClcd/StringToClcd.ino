#include <CLCD.h>

void setup()
{
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)
}

void loop()
{
  CLCD.print(" Hello World !");
  CLCD.setCursor(2,0);  // Second Line 0 position
  CLCD.print("I Love ROBOLINK");
  
  delay(1000);
  
  CLCD.clearLine1(); // Display Clear Line 1
  
  CLCD.print("HUNOI for ");
  
  CLCD.clearLine2(); // Display Clear Line 2
  
  CLCD.setCursor(2,9);  // Second Line 8 position
  CLCD.print("Arduino");
  
  delay(1000);
  
  CLCD.clearAll(); // Display Clear Line All
}



