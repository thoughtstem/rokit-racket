/*
  PulseModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef PulseModule_h
#define PulseModule_h

#include "Arduino.h"


class PulseModule
{
  int _id;  
  word _duration;
  boolean _updated;
  unsigned long _time;
  boolean _do;
  
public:
  PulseModule(byte id);
  
  void update(byte id);
  void action();
  void reset();
  float process();  
};

#endif /*PulseModule_h */

