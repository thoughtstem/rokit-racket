/*
  PulseModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************
#include "UnityRobot.h"
#include "PulseModule.h"


//******************************************************************************
//* Constructors
//******************************************************************************
PulseModule::PulseModule(byte id)
{
  _id = id;
  reset();
}

//******************************************************************************
//* Public Methods
//******************************************************************************
void PulseModule::update(byte id)
{
  if(id == _id)
  {
    _updated = true;
    _do = false;
    UnityRobot.pop(&_duration);
  }
}
  
void PulseModule::action()
{
  if(_updated == true)
  {
    if(_duration > 0)
    {
      _do = true;
      _time = millis();
      _updated = false;
    }
  }
}
  
void PulseModule::reset()
{
  _updated = false;
  _duration = 0;
  _do = false;
}
  
float PulseModule::process()
{
  if(_do == true)
  {
    unsigned long delta = millis() - _time;
    if(_duration > (word)delta)
    {
      return 1 - (float)delta / (float)_duration;
    }
    else
    {
      _duration = 0;
      _do = false;
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

//******************************************************************************
//* Private Methods
//******************************************************************************

