/*********************************
  //CubeWorks 3 Step All Example
  //2015-08-18 RoboWorks & RoboLink
**********************************/
#include <SmartInventor.h>
#include <Servo.h>

#include "ProgramSelection.h"

#include "CrabBot.h"            //1
#include "Fan.h"                //2
#include "LineTracer.h"         //3 Train
#include "Surfing.h"            //4 Rodeo servo 1
#include "AutoCrossBar.h"       //5
#include "AutoCart.h"           //6
#include "CarrierBot.h"         //7
#include "RobotCleaner.h"       //8
#include "Viking.h"             //9
#include "PuttingBot.h"         //10
#include "FlagGame.h"           //11

#include "RemoconCar.h"

#define NORMAL  0
#define UPGRADE 1

#define DipSw1  8
#define DipSw2  9
#define DipSw3  10

void setup()
{
  pinMode(DipSw1, INPUT_PULLUP);
  pinMode(DipSw2, INPUT_PULLUP);
  pinMode(DipSw3, INPUT_PULLUP);
  delay(500);

  Serial.begin(9600);
  Serial.print("- Cubeworks - ");
  Serial.print("ver : ");
  Serial.print(160304);
  Serial.end();

  pinMode(8, INPUT_PULLUP);     //DipSw1
  pinMode(9, INPUT_PULLUP);     //DipSw2
  pinMode(10, INPUT_PULLUP);    //DipSw3

  delay(250);
}

void loop()
{
  //Cubeworks Step 3 Only
  
  byte programNumber =  ProgramSelection(NORMAL);  //sensor or remocon use

  if (programNumber == 1)  CrabBot();
  else if (programNumber == 2)  Viking();
  else if (programNumber == 3)  LineTracer();
  else if (programNumber == 4)  Surfing();
  else if (programNumber == 5)  FlagGame();
  else if (programNumber == 6)  Fan();
  else if (programNumber == 7)  AutoCrossBar();
  else if (programNumber == 8)  AutoCart();
  else if (programNumber == 9)  PuttingBot();
  else if (programNumber == 10)  CarrierBot();
  else if (programNumber == 11)  RobotCleaner();
  else RemoconCar();  //RemoteCar
}
