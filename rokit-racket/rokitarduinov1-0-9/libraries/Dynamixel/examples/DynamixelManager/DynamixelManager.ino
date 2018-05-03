/*
  Name: Dynamixel Manager
  B/D: Ardu-X 200
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#include <string.h>
#include <Dynamixel.h>

#define MAX_CMD_LENGTH  50
#define DIR_PIN  2
#define DIR_TX  HIGH
#define DIR_RX  LOW
#define PC_BAUD  57600 // bps
#define DXL_BAUD  1 // baud number

int baudNum = DXL_BAUD;
char cmdBuff[MAX_CMD_LENGTH];
int cmdIndex = 0;
char* cmd;
char* arg1;
char* arg2;
char* arg3;
char* arg4;

void setup()
{
  Dynamixel.attachSerial(&Serial1);
  Dynamixel.attachPins(DIR_PIN, DIR_TX, DIR_RX);
  Dynamixel.begin(Dynamixel.baudnumToSpeed(baudNum));
  
  Serial.begin(PC_BAUD);
  printIntro();
}

void loop()
{
  if(Serial.available() > 0)
  {
    int input = Serial.read();
    Serial.write(input); // echo
    cmdBuff[cmdIndex++] = (char)input;
    if(cmdIndex >= MAX_CMD_LENGTH)
    {
      cmdIndex = 0;
      printMaxLengthError();
    }
    else
    {
      if(cmdBuff[cmdIndex - 1] == '\n')
      {
        cmdBuff[cmdIndex - 1] = 0; // end of string
        cmd = strtok(cmdBuff, " "); // spilt command
        arg1 = strtok(0, " "); // spilt argument1
        arg2 = strtok(0, " "); // spilt argument2
        arg3 = strtok(0, " "); // spilt argument3
        arg4 = strtok(0, " "); // spilt argument4
        
        if(strcmp(cmd, "help") == 0)
          cmdHelp();
        else if(strcmp(cmd, "baud") == 0)
          cmdBaud(arg1);
        else if(strcmp(cmd, "scan") == 0)
          cmdScan();
        else if(strcmp(cmd, "search") == 0)
          cmdSearch();
        else if(strcmp(cmd, "go") == 0)
          cmdGo(arg1, arg2);
        else if(strcmp(cmd, "id") == 0)
          cmdID(arg1, arg2);
        else if(strcmp(cmd, "write") == 0)
          cmdWrite(arg1, arg2, arg3, arg4);
        else if(strcmp(cmd, "read") == 0)
          cmdRead(arg1, arg2, arg3);
        else
        {
          if(cmdIndex - 1 == 0)
            printPrompt();
          else
            printCmdError();
        }
        cmdIndex = 0;
      }
    }
  }
}
