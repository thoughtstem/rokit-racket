#include <CLCD.h>

void setup()
{
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)
  Serial.begin(9600);  // begin serial
}

void loop()
{
// when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    CLCD.clearAll(); // Display Clear
    // read all the available characters
    int i = 0;
    while (Serial.available() > 0) {
      // display each character to the CLCD
      i++;
      if (i==17) CLCD.setCursor(2,0);  // Next Line
      CLCD.Data(Serial.read());  // Serial read data => Display CLCD
    }
  }
}



