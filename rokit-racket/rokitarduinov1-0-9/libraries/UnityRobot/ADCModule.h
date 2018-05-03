/*
  ADCModule.h - UnityRobot Module library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef ADCModule_h
#define ADCModule_h

#include "Arduino.h"


class ADCModule
{
public:
	ADCModule(int id, int pin);

	void flush();

private:
	int _id;
	int _pin;	
};

#endif /*ADCModule_h */

