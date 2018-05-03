#include <SmartInventor.h>
#include <Servo.h> 

//ver. CubeWorks Surfing

void Surfing() 
{
  Servo myservo1; 
  myservo1.attach(27);

  byte angle1 = 90;

  byte speed = 100;
  byte score = 22;

  int leftSensor = 0;
  int rightSensor = 0;
  int angleLevel = 1;

  //□ □ □ □ □ □ □ □
  //11,12,13,14,15,16,17,18
  //Led Output
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
    pinMode(thisPin, OUTPUT);  
  } 

  myservo1.write(angle1);

  while(1)
  {

    leftSensor = analogRead(A2);
    rightSensor =  analogRead(A0);

    if (leftSensor < rightSensor) 
    {
      if(angle1 < 179) angle1 -= angleLevel;
    }
    else           
    {  
      if(angle1 > 0) angle1 += angleLevel;
    }

    myservo1.write(angle1);

    //down cow
    if((angle1 < 30) ||(angle1 > 140))
    {
      if (angle1 < 30)   myservo1.write(0);
      if (angle1 > 140) myservo1.write(180);

      for (byte i = 0; i< 3; i++)
      {
        SmartInventor.Buzz(740,2); 
        delay(500);
      }

      angle1 = 90;
      speed = 100;
      angleLevel = 1;
      score = 22;
      //Led OFF
      for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
        digitalWrite(thisPin, LOW);  
      } 
    }

    SmartInventor.Buzz(1160,20); 
    delay(speed);

    if(SmartInventor.TimeCheckMillis(1000))  
    {
      speed = speed - 5;
      if (speed <= 0) speed = 5;

      if(speed<30) angleLevel = 7;
      else if(speed<50) angleLevel = 5;
      else if(speed<70) angleLevel = 3;
      else if(speed<80) angleLevel = 2;

      score ++;
      if(score > 36) score = 36;
    }

    digitalWrite(score/2,HIGH);
  }
} 
