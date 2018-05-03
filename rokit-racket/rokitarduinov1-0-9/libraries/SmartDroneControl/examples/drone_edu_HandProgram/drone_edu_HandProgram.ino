
#include <SmartInventor.h>
#include <SmartDroneControl.h>

#include "ProgramSelection.h"

#include "SmartDrone1_1.h"
#include "SmartDrone1_2.h"
#include "SmartDrone1_3.h"
#include "SmartDrone2_1.h"
#include "SmartDrone2_2.h"
#include "SmartDrone3.h"
#include "SmartDrone4.h"
#include "SmartDrone5.h"

void setup() {
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  delay(500);
}

void loop() {

  byte programNumber =  ProgramSelection(0);  //sensor or remocon use
  {
    if (programNumber == 1)       SmartDrone1_1();
    else if (programNumber == 2)  SmartDrone1_2();
    else if (programNumber == 3)  SmartDrone1_3();    
    else if (programNumber == 4)  SmartDrone2_1();
    else if (programNumber == 5)  SmartDrone2_2();    
    else if (programNumber == 6)  SmartDrone3();    
    else if (programNumber == 7)  SmartDrone4();
    else if (programNumber == 8)  SmartDrone5();
  }

}
