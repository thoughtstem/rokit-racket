#include <RokitFlying.h>

void Program_1()
{
  byte speed = 100;

  RokitFlying.WiredRemoconUse();
  RokitFlying.DCMotorUse();

  while (1)
  {
    int keyData = RokitFlying.WiredRemocon();
    // Serial.println(keyData);

    if (keyData == KEY_U)       RokitFlying.DCMove(forward, speed);
    else if (keyData == KEY_D)  RokitFlying.DCMove(backward, speed);
    else if (keyData == KEY_L)  RokitFlying.DCMove(left_turn, speed);
    else if (keyData == KEY_R)  RokitFlying.DCMove(right_turn, speed);
    else                        RokitFlying.DCMove(stop, speed);

  }
}

