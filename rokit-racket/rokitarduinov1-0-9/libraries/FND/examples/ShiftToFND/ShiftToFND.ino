#include <FND.h>
//using 7segment type - CommonCathod (EX : 3261CSR)

int InputSwitch = 15;
int CheckTime = 0;

void setup() {
  FND.begin(8,9,10);  //si ,sck, rck pin
  pinMode(InputSwitch, INPUT_PULLUP);
  FND.setNumber(1234);
}

void loop() {
  int sensorVal = digitalRead(InputSwitch);
  unsigned long time = (millis()/1000);

  if (time > CheckTime)
  {
    if (sensorVal == HIGH)    FND.rightShift();   
    else FND.leftShift();
    
    CheckTime = time;
  }
  FND.dynamicDisplay();
}
