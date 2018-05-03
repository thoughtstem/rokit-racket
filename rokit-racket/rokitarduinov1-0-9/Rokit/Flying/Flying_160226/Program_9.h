#include <RokitFlying.h>

void Program_9()
{

  byte speedList[] = {50, 75, 100};
  byte speedLv = 1;
  byte speed = speedList[speedLv];

  byte angle = 90;

  RokitFlying.TVRemoconUse();
  RokitFlying.DCMotorUse();

  Servo myservo1;
  myservo1.attach(6);
  myservo1.write(angle);


  while (1)
  {
    int keyData =  RokitFlying.TVRemoconData();
    //Serial.println(keyData);

    if (keyData == KEY_U)       RokitFlying.DCMove(forward, speed);
    else if (keyData == KEY_D)  RokitFlying.DCMove(backward, speed);
    else if (keyData == KEY_L)  RokitFlying.DCMove(left_turn, speed);
    else if (keyData == KEY_R)  RokitFlying.DCMove(right_turn, speed);
    else                        RokitFlying.DCMove(stop, speed);

    if (keyData == KEY_F1)
    {
      if (speedLv > 0)  speedLv--;
      speed = speedList[speedLv];
      delay(500);
    }

    else if (keyData == KEY_F2)
    {
      if (speedLv < 2)  speedLv++;
      speed = speedList[speedLv];
      delay(500);
    }


    if (keyData == KEY_F3)
    {
      if (angle > 0)
      {
        angle--;
        myservo1.write(angle);
        delay(10);
      }
    }

    else if (keyData == KEY_F4)
    {
      if (angle < 180)
      {
        angle++;
        myservo1.write(angle);
        delay(10);
      }
    }
  }
}

