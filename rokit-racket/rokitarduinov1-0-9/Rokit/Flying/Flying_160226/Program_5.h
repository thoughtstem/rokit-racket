#include <RokitFlying.h>

void Program_5()
{
  int sensor1 = 10;
  int sensor2 = 11;

  byte speed = 80;

  RokitFlying.DCMotorUse();

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);

  while (1)
  {
    int senVal1 = digitalRead(sensor1);
    int senVal2 = digitalRead(sensor2);

    if ((senVal1 == LOW) || (senVal2 == LOW))
    {
      RokitFlying.DCMove(backward, speed);
      delay(500);
      RokitFlying.DCMove(left_turn, speed);
      delay(500);
      RokitFlying.DCMove(forward, speed);
    }
    else if (senVal1 == LOW)
    {
      RokitFlying.DCMove(left_turn, speed);
    }
    else if (senVal2 == LOW)
    {
      RokitFlying.DCMove(right_turn, speed);
    }
    else
    {
      RokitFlying.DCMove(forward, speed);
    }
  }
}
