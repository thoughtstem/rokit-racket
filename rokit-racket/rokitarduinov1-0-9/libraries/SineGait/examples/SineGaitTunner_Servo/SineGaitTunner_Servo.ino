/*
  Name: SineGait Tunner
  B/D: Ardu-X 200
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#include <Ansiterm.h>
#include <SineGait.h>
#include <Servo.h>

#define JOINT_NUM 4
int pins[] = {47, 48, 49, 23};


#define ROW_START 2
#define ROW_PERIOD 3
#define ROW_JOINT 5
#define COL_START 15
#define COL_PERIOD 15
#define COL_AMP 6
#define COL_SPD 13
#define COL_PHS 20
#define COL_BAL 27
#define COL_CEN 34
#define COL_DIR 41
#define COL_WIDTH 7

SineGait sineGait(JOINT_NUM);
Servo servo[JOINT_NUM];
Ansiterm ansi;

boolean processStart = false;
float period = 1;
float amplitude[JOINT_NUM];
float speed[JOINT_NUM];
float phase[JOINT_NUM];
float balance[JOINT_NUM];
int center[JOINT_NUM];
int dir[JOINT_NUM];
int currentRow;
int currentColumn;

void setup()
{
  for(int i=0; i<JOINT_NUM; i++)
  {
    servo[i].attach(pins[i]);
    amplitude[i] = 0;
    speed[i] = 1;
    phase[i] = 0;
    balance[i] = 0;
    center[i] = 90;
    dir[i] = 1;
  }
  
  Serial.begin(57600);
  // Draw screen
  ansi.eraseScreen();
  ansi.home();  
  ansi.setBackgroundColor(BLUE);
  ansi.setForegroundColor(GREEN);
  Serial.println("------------Sine Gait Tunner(Servo)-----------");
  ansi.setBackgroundColor(BLACK);
  ansi.setForegroundColor(WHITE);
  Serial.println("Start/Stop:");
  Serial.println("Period(sec):");
  Serial.println("ID   Amp    Spd    Phs    Bal    Cen    Dir");
  for(int i=0; i<JOINT_NUM; i++)
  {
    Serial.print("[");
    Serial.print(i, DEC);
    Serial.println("]  ");
  }
  ansi.setForegroundColor(GREEN);
  
  DrawBool(ROW_START, COL_START, processStart);
  DrawFloat(ROW_PERIOD, COL_PERIOD, period);
  
  for(int i=0; i<JOINT_NUM; i++)
  {
    DrawInt(ROW_JOINT + i, COL_AMP, (int)amplitude[i]);
    DrawFloat(ROW_JOINT + i, COL_SPD, speed[i]);
    DrawFloat(ROW_JOINT + i, COL_PHS, phase[i]);
    DrawFloat(ROW_JOINT + i, COL_BAL, balance[i]);
    DrawInt(ROW_JOINT + i, COL_CEN, center[i]);
    DrawInt(ROW_JOINT + i, COL_DIR, dir[i]);
  }  
  
  currentRow = ROW_START;
  currentColumn = COL_START;  
  ansi.xy(currentColumn, currentRow); // cursor
}

void loop()
{  
  // input
  while(Serial.available())
  {
    int keyInput = Serial.read();
    if(keyInput == 27)
    {
      while(Serial.available() == 0);
      int keyInput2 = Serial.read();
      if(keyInput2 == 91)
      {
        while(Serial.available() == 0);
        int keyInput3 = Serial.read();
        if(keyInput3 == 65) // up arrow
        {          
          if(currentRow == ROW_JOINT)
          {
            currentRow = ROW_PERIOD;
            currentColumn = COL_PERIOD;
          }
          else if(currentRow != ROW_START)
            currentRow--;
        }
        else if(keyInput3 == 66) // down arrow
        {
          if(currentRow == ROW_PERIOD)
          {
            currentRow = ROW_JOINT;
            currentColumn = COL_AMP;
          }
          else if(currentRow < (ROW_JOINT + JOINT_NUM - 1))
            currentRow++;
        }
        else if(keyInput3 == 67) // right arrow
        {
          if(currentRow >= ROW_JOINT)
          {
            if(currentColumn < COL_DIR)
              currentColumn += COL_WIDTH;
          }
        }
        else if(keyInput3 == 68) // left arrow
        {
          if(currentRow >= ROW_JOINT)
          {
            if(currentColumn > COL_AMP)
              currentColumn -= COL_WIDTH;            
          }
        }
      }
    }
    else if(keyInput == '[')
    {
      if(currentRow == ROW_START)
      {
        processStart = false;
        sineGait.stop();
        DrawBool(currentRow, currentColumn, processStart);
      }
      else if(currentRow == ROW_PERIOD)
      {
        period = clamp(period - 0.01, 0.1, 3);
        DrawFloat(currentRow, currentColumn, period);
      }
      else
      {
        int id = currentRow - ROW_JOINT;
        if(currentColumn == COL_AMP)
        {
          amplitude[id] = clamp(amplitude[id] - 1, -90, 90);
          DrawInt(currentRow, currentColumn, (int)amplitude[id]);
        }
        else if(currentColumn == COL_SPD)
        {
          speed[id] = clamp(speed[id] - 0.1, 0, 3);
          DrawFloat(currentRow, currentColumn, speed[id]);
        }
        else if(currentColumn == COL_PHS)
        {
          phase[id] = clamp(phase[id] - 0.01, -1, 1);
          DrawFloat(currentRow, currentColumn, phase[id]);
        }
        else if(currentColumn == COL_BAL)
        {
          balance[id] = clamp(balance[id] - 0.01, -1, 1);
          DrawFloat(currentRow, currentColumn, balance[id]);
        }
        else if(currentColumn == COL_CEN)
        {
          center[id] = clamp(center[id] - 1, 0, 180);
          DrawInt(currentRow, currentColumn, center[id]);
        }
        else if(currentColumn == COL_DIR)
        {
          dir[id] = -1;
          DrawInt(currentRow, currentColumn, dir[id]);
        }
      }
    }
    else if(keyInput == ']')
    {
      if(currentRow == ROW_START)
      {
        processStart = true;
        sineGait.start();
        DrawBool(currentRow, currentColumn, processStart);
      }
      else if(currentRow == ROW_PERIOD)
      {
        period = clamp(period + 0.01, 0.1, 3);
        DrawFloat(currentRow, currentColumn, period);
      }
      else
      {
        int id = currentRow - ROW_JOINT;
        if(currentColumn == COL_AMP)
        {
          amplitude[id] = clamp(amplitude[id] + 1, -90, 90);
          DrawInt(currentRow, currentColumn, (int)amplitude[id]);
        }
        else if(currentColumn == COL_SPD)
        {
          speed[id] = clamp(speed[id] + 0.1, 0, 3);
          DrawFloat(currentRow, currentColumn, speed[id]);
        }
        else if(currentColumn == COL_PHS)
        {
          phase[id] = clamp(phase[id] + 0.01, -1, 1);
          DrawFloat(currentRow, currentColumn, phase[id]);
        }
        else if(currentColumn == COL_BAL)
        {
          balance[id] = clamp(balance[id] + 0.01, -1, 1);
          DrawFloat(currentRow, currentColumn, balance[id]);
        }
        else if(currentColumn == COL_CEN)
        {
          center[id] = clamp(center[id] + 1, 0, 180);
          DrawInt(currentRow, currentColumn, center[id]);
        }
        else if(currentColumn == COL_DIR)
        {
          dir[id] = 1;
          DrawInt(currentRow, currentColumn, dir[id]);
        }
      } 
    }
    
    sineGait.setPeriod(period);
    for(int i=0; i<JOINT_NUM; i++)
      sineGait.setJoint(i, amplitude[i], balance[i], phase[i], speed[i]);
    
    ansi.xy(currentColumn, currentRow); // cursor 
  }
  
  sineGait.process();
  if(processStart == true)
  {
    for(int i=0; i<JOINT_NUM; i++)
    {
      servo[i].write(sineGait.getValue(i, center[i], 1, dir[i]));
    }
  }
}

void DrawFloat(int row, int col, float value)
{
  ansi.xy(col, row); // cursor
  for(int i=0; i<COL_WIDTH; i++)
    Serial.print(" ");
  ansi.xy(col, row); // cursor
  Serial.print(value, 2);
}

void DrawInt(int row, int col, int value)
{
  ansi.xy(col, row); // cursor
  for(int i=0; i<COL_WIDTH; i++)
    Serial.print(" ");
  ansi.xy(col, row); // cursor
  Serial.print(value, DEC);
}

void DrawBool(int row, int col, boolean value)
{
  ansi.xy(col, row); // cursor  
  for(int i=0; i<COL_WIDTH; i++)
    Serial.print(" ");
  ansi.xy(col, row); // cursor
  if(value == true)
    Serial.print("ON");
  else
    Serial.print("OFF");
}

float clamp(float value, float minValue, float maxValue)
{
  if(value < minValue)
    value = minValue;
  else if(value > maxValue)
    value = maxValue;
  
  return value;
}

