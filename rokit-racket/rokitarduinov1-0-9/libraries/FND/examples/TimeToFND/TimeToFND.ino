#include <FND.h>
//using 7segment type - CommonCathod (EX : 3261CSR)

void setup() {
  FND.begin(8,9,10);  //si ,sck, rck pin;
}

void loop() {
  char time = (millis()/1000);
  FND.setNumber(time);
  FND.dynamicDisplay();  //count 1second
}
