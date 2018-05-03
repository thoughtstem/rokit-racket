#include <RokitFlying.h>

void Program_7()
{
  byte speed = 80;
  RokitFlying.TVRemoconUse();
  RokitFlying.DCMotorUse();

  while (1)
  {
    int keyData =  RokitFlying.TVRemoconData();
    //Serial.println(keyData);

    if (keyData == KEY_U)       RokitFlying.DCMotor(M1, CCW, speed);
    else if (keyData == KEY_D)  RokitFlying.DCMotor(M1, CW, speed);
    else if (keyData == KEY_L)  RokitFlying.DCMotor(M2, CW, speed);
    else if (keyData == KEY_R)  RokitFlying.DCMotor(M2, CCW, speed);
    else                        RokitFlying.DCMove(stop, speed);

  }
}

