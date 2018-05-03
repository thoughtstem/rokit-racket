/*=============================================================================
  //Rokit-Flying
  //2016-01-14 RoboLink
  -------------------------------------------------------------------------------

  =============================================================================*/
#include <RokitFlying.h>
#include <Servo.h>

#include "ProgramSelect.h"
#include "Program_1.h"            //1
#include "Program_2.h"            //2
#include "Program_3.h"            //3
#include "Program_4.h"            //4
#include "Program_5.h"            //5
#include "Program_6.h"            //6
#include "Program_7.h"            //7
#include "Program_8.h"            //8
#include "Program_9.h"            //9

void setup()
{
  Serial.begin(9600);  

  Serial.print("ver : ");
  Serial.print(160226);
    
  RokitFlying.LedPerformance(0,100);
}

void loop()
{
  int programNumber = ProgramSelect();

  if (programNumber == 1)  Program_1();
  else if (programNumber == 2)  Program_2();
  else if (programNumber == 3)  Program_3();
  else if (programNumber == 4)  Program_4();
  else if (programNumber == 5)  Program_5();
  else if (programNumber == 6)  Program_6();
  else if (programNumber == 7)  Program_7();
  else if (programNumber == 8)  Program_8();
  else if (programNumber == 9)  Program_9();

  else Program_1();
}



