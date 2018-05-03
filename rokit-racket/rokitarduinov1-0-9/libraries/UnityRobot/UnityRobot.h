/*
  UnityRobot.h - UnityRobot library
  Copyright (C) 2014 Robolink.  All rights reserved.
*/

#ifndef UnityRobot_h
#define UnityRobot_h

#include "Arduino.h"

#define MAX_ARGUMENT_BYTES    116

#define CMD_START         0x80 // start
#define CMD_EXIT	      0x81 // exit
#define CMD_UPDATE        0x82 // update
#define CMD_ACTION        0x83 // action
#define CMD_READY         0x84 // ready
#define CMD_PING	      0x85 // ping

extern "C"
{
// callback function types
    typedef void (*callbackUpdate)(byte);
	typedef void (*callbackCommand)(void);	
}


// TODO make it a subclass of a generic Serial/Stream base class
class UnityRobotClass
{
public:
	UnityRobotClass(HardwareSerial *s);

	void attachSerial(HardwareSerial *s);
	void begin(long speed);
    void process(void);
	void select(byte id);	
	void flush();
/* attach & detach callback functions to messages */
    void attach(int cmd, callbackUpdate newFunction);
	void attach(int cmd, callbackCommand newFunction);
	void detach(int cmd);
/* type convert methods */
	boolean push(byte value);
	boolean push(word value);
	boolean push(short value);
	boolean push(byte* value, byte count);
	boolean pop(byte* value);
	boolean pop(word* value);
	boolean pop(short* value);
	boolean pop(byte* value, byte count);

private:
    HardwareSerial* UnityRobotSerial;

	boolean readyReceived;
	byte processUpdate;
	byte ID;
	byte numData;
	byte currentNumData;
    byte storedData[MAX_ARGUMENT_BYTES + (MAX_ARGUMENT_BYTES / 8) + 1];
	byte numArgument;
	byte storedArgument[MAX_ARGUMENT_BYTES];
	
/* callback functions */
    callbackUpdate currentCallbackUpdate;
    callbackCommand currentCallbackAction;
	callbackCommand currentCallbackStart;
	callbackCommand currentCallbackExit;
	callbackCommand currentCallbackReady;
/* private methods ------------------------------ */
    void Reset(void);
};

extern UnityRobotClass UnityRobot;

#endif /*UnityRobot_h */

