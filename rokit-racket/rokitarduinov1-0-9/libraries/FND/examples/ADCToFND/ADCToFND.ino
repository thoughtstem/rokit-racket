#include <FND.h>
//using 7segment type - CommonCathod (EX : 3261CSR)

void setup() {
  FND.begin(8,9,10);  //si ,sck, rck pin;
}

void loop() {
  int sensorValue = analogRead(A0);
  FND.setNumber(sensorValue);
  FND.dynamicDisplay();
}
