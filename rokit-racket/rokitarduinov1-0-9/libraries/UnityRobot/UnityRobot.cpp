/*
  UnityRobot.cpp - UnityRobot library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/


//******************************************************************************
//* Includes
//******************************************************************************

#include "UnityRobot.h"
#include "HardwareSerial.h"

extern "C" {
#include <string.h>
#include <stdlib.h>
}

//******************************************************************************
//* Constructors
//******************************************************************************

UnityRobotClass::UnityRobotClass(HardwareSerial* s) : UnityRobotSerial(s)
{
}

//******************************************************************************
//* Public Methods
//******************************************************************************

void UnityRobotClass::attachSerial(HardwareSerial* s)
{
	UnityRobotSerial = s;
}

void UnityRobotClass::begin(long speed)
{
	UnityRobotSerial->begin(speed);
	readyReceived = false;
	processUpdate = 0;
	Reset();
}

void UnityRobotClass::process(void)
{
	while(UnityRobotSerial->available() > 0)
	{
		byte bit = 1;
		int inputData = UnityRobotSerial->read(); // this is 'int' to handle -1 when no data	

		if(inputData >= 0)
		{
			if(inputData & 0x80)
			{
				if(inputData == CMD_PING)
				{
					UnityRobotSerial->write(CMD_PING);				
				}
				else if(inputData == CMD_START)
				{
					if(currentCallbackStart)
						(*currentCallbackStart)();

					UnityRobotSerial->write(CMD_READY);
				}
				else if(inputData == CMD_EXIT)
				{
					if(currentCallbackExit)
						(*currentCallbackExit)();
				}
				else if(inputData == CMD_READY)
				{
					readyReceived = true;
				}
				else if(inputData == CMD_ACTION)
				{
					if(processUpdate > 0)
					{
						if(currentCallbackAction)
							(*currentCallbackAction)();

						UnityRobotSerial->write(CMD_READY);
						processUpdate = 0;
					}
				}
			
				if(inputData == CMD_UPDATE)
					processUpdate = 1;
				else
					Reset();
			}
			else if(processUpdate > 0)
			{
				if(processUpdate == 1)
				{
					ID = inputData;
					processUpdate = 2;
				}
				else if(processUpdate == 2)
				{
					numData = inputData;
					if(numData > MAX_ARGUMENT_BYTES)
						Reset();
					else
					{
						processUpdate = 3;
						currentNumData = 0;
					}
				}
				else if(processUpdate == 3)
				{
					if(currentNumData < numData)
						storedData[currentNumData++] = inputData;

					if(currentNumData >= numData)
					{
						// Decoding 7bit bytes
						numData = 0;
						for(int i=0; i<currentNumData; i++)
						{
							if(bit == 1)
							{
								storedData[numData] = storedData[i] << bit;
								bit++;
							}
							else if(bit == 8)
							{
								storedData[numData] |= storedData[i];
								bit = 1;
							}
							else
							{
								storedData[numData++] |= storedData[i] >> (7 - bit + 1);
								storedData[numData] = storedData[i] << bit;
								bit++;
							}
						}

						currentNumData = 0;
						if(currentCallbackUpdate)
							(*currentCallbackUpdate)(ID);

						processUpdate = 1;
					}
				}
			}
			else
				Reset();
		}
	}

	if(readyReceived == true)
	{
		UnityRobotSerial->write(CMD_UPDATE);
		
		if(currentCallbackReady)
			(*currentCallbackReady)();

		UnityRobotSerial->write(CMD_ACTION);
		readyReceived = false;
	}
}

void UnityRobotClass::select(byte id) 
{
	UnityRobotSerial->write(id & 0x7F);
	numArgument = 0;
}

void UnityRobotClass::flush() 
{
	float a = numArgument / 7;
	float b = numArgument % 7;
	byte addedNum = (byte)a;
	if(b > 0)
		addedNum++;

	UnityRobotSerial->write((numArgument + addedNum) & 0x7F);
	// Encoding 7bit bytes
	byte bit = 1;
	byte value = 0;
	for(byte i=0; i<numArgument; i++)
	{
		UnityRobotSerial->write((value | (storedArgument[i] >> bit)) & 0x7F);
		if(bit == 7)
		{
			UnityRobotSerial->write(storedArgument[i] & 0x7F);
			bit = 1;
			value = 0;
		}
		else
		{
			value = storedArgument[i] << (7 - bit);
			if(i == (numArgument - 1))
				UnityRobotSerial->write(value & 0x7F);
			bit++;
		}		
	}
}

// generic callbacks
void UnityRobotClass::attach(int cmd, callbackUpdate newFunction)
{
	if(cmd == CMD_UPDATE)
		currentCallbackUpdate = newFunction;
}

void UnityRobotClass::attach(int cmd, callbackCommand newFunction)
{
	if(cmd == CMD_ACTION)
		currentCallbackAction = newFunction;
	else if(cmd == CMD_START)
		currentCallbackStart = newFunction;
	else if(cmd == CMD_EXIT)
		currentCallbackExit = newFunction;
	else if(cmd == CMD_READY)
		currentCallbackReady = newFunction;
}

void UnityRobotClass::detach(int cmd)
{
	switch(cmd)
	{
	case CMD_UPDATE:
		currentCallbackUpdate = NULL;
		break;

	case CMD_ACTION:
		currentCallbackAction = NULL;
		break;

	case CMD_START:
		currentCallbackStart = NULL;
		break;

	case CMD_EXIT:
		currentCallbackExit = NULL;
		break;

	case CMD_READY:
		currentCallbackReady = NULL;
		break;
	}
}
boolean UnityRobotClass::push(byte value)
{
	if((MAX_ARGUMENT_BYTES - numArgument) < 1)
		return false;

	storedArgument[numArgument++] = value;
	return true;
}

boolean UnityRobotClass::push(word value)
{
	if((MAX_ARGUMENT_BYTES - numArgument) < 2)
		return false;

	storedArgument[numArgument++] = (byte)(value & 0xFF);
	storedArgument[numArgument++] = (byte)((value >> 8) & 0xFF);
	return true;
}

boolean UnityRobotClass::push(short value)
{
	word binary;
	if(value < 0)
	{
		value *= -1;
		binary = (word)value;
		binary |= 0x8000;
	}
	else
		binary = (word)value;

	return push(binary);
}

boolean UnityRobotClass::push(byte* value, byte count)
{
	if((MAX_ARGUMENT_BYTES - numArgument) < count)
		return false;

	for(byte i=0; i<count; i++)
		storedArgument[numArgument + i] = value[i];
	numArgument += count;
	return true;
}

boolean UnityRobotClass::pop(byte* value)
{
	if((numData - currentNumData) < 1)
		return false;

	*value = storedData[currentNumData++];
	return true;
}

boolean UnityRobotClass::pop(word* value)
{
	if((numData - currentNumData) < 2)
		return false;

	*value = storedData[currentNumData++];
	*value |= (storedData[currentNumData++] << 8) & 0xFF00;
	return true;
}

boolean UnityRobotClass::pop(short* value)
{
	word binary;
	if(pop(&binary) == false)
		return false;

	*value = (short)(binary & 0x7FFF);
	if(binary & 0x8000)
		*value *= -1;
	return true;
}

boolean UnityRobotClass::pop(byte* value, byte count)
{
	if((numData - currentNumData) < count)
		return false;

	for(byte i=0; i<count; i++)
		*(value + i) = storedData[currentNumData + i];
	currentNumData += count;
	return true;
}


//******************************************************************************
//* Private Methods
//******************************************************************************

// resets the system state upon a SYSTEM_RESET message from the host software
void UnityRobotClass::Reset(void)
{
	if(processUpdate > 0)
		UnityRobotSerial->write(CMD_READY);
	
	processUpdate = 0;
	numData = 0;
	currentNumData = 0;
	numArgument = 0;
}


UnityRobotClass UnityRobot(&Serial);


