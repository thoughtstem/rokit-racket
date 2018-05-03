/*
 Name: Herkulex Manager
 B/D: Ardu-X 200
 Copyright (C) 2014 RoboLink.  All rights reserved.
 */

#include <string.h>
#include <Herkulex.h>

#define MAX_CMD_LENGTH  50
#define PC_BAUD  57600 // bps
#define HKS_BAUD  0x10 // baud number

int baudNum = HKS_BAUD;
char cmdBuff[MAX_CMD_LENGTH];
int cmdIndex = 0;
char* cmd;
char* arg1;
char* arg2;

void setup()
{
  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);
  Herkulex.beginSerial1(BaudnumToSpeed(baudNum));

  Serial.begin(PC_BAUD);
  printIntro();
}

void loop()
{
  if(Serial.available() > 0)
  {
    int input = Serial.read();    
    Serial.write(input); // echo
    if(input == '\r')
    {
      input = '\n';
      Serial.write(input); // echo
    }
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
        else if(strcmp(cmd, "read") == 0)
          cmdRead(arg1);
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

