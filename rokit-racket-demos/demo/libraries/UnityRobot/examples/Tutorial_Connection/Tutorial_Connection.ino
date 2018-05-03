/*
  Name: Tutorial Connection
  B/D: Any Board
  Author: Jaehong (jhoh@robolink.co.kr)
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#include <UnityRobot.h>

void setup()
{
  UnityRobot.begin(57600);
}

void loop()
{
  UnityRobot.process();
}
