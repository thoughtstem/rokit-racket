#include <CLCD.h>

void setup()
{
  CLCD.begin(8,9,10);  // initialize CLCD (si ,sck, rck pin)
}

void loop()
{
  int sensorValue = analogRead(A0);
  CLCD.clearAll();
  CLCD.print(sensorValue);
  delay(100);
}
