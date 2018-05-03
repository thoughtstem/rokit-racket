/*
  DigitalModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************
#include "UnityRobot.h"
#include "DigitalModule.h"


//******************************************************************************
//* Constructors
//******************************************************************************

DigitalModule::DigitalModule(int id, int pin)
{
	_id = id;
	_pin = pin;
	_mode = 0; // output
}

//******************************************************************************
//* Public Methods
//******************************************************************************

void DigitalModule::begin()
{	
	reset();
}

void DigitalModule::reset()
{
	setPinMode();
	if(_mode == 0) // output
	{
		_state = 0;
		digitalWrite(_pin, _state);
	}
}

void DigitalModule::update(int id)
{
	if(id == _id)
	{
		byte newMode;
		UnityRobot.pop(&newMode);
		UnityRobot.pop(&_state);

		if(_mode != newMode)
		{
			_mode = newMode;
			setPinMode();
		}
	}
}

void DigitalModule::action()
{
	if(_mode == 0) // output
	{
		digitalWrite(_pin, _state);
	}
}

void DigitalModule::flush()
{
	if(_mode != 0) // input/input_pullup
	{
		_state = digitalRead(_pin);
		UnityRobot.select(_id);
		UnityRobot.push(_state);
		UnityRobot.flush();
	}
}

//******************************************************************************
//* Private Methods
//******************************************************************************

void DigitalModule::setPinMode()
{
	if(_mode == 0)
		pinMode(_pin, OUTPUT);
	else if(_mode == 1)
		pinMode(_pin, INPUT);
	else if(_mode == 2)
		pinMode(_pin, INPUT_PULLUP);
}