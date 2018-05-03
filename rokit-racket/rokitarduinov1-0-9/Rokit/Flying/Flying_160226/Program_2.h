#include <RokitFlying.h>

void Program_2()
{
  byte speed = 80;

  RokitFlying.WiredRemoconUse();
  RokitFlying.DCMotorUse();

  while (1)
  {
    int keyData = RokitFlying.WiredRemocon();
    // Serial.println(keyData);

    if (keyData == KEY_U)       RokitFlying.DCMove(forward, speed);
    else if (keyData == KEY_D)  RokitFlying.DCMove(backward, speed);
    else if (keyData == KEY_L)  RokitFlying.DCMove(left, speed);
    else if (keyData == KEY_R)  RokitFlying.DCMove(right, speed);
    else if (keyData == KEY_F1) RokitFlying.DCMove(left_turn, speed);
    else if (keyData == KEY_F2) RokitFlying.DCMove(right_turn, speed);
    else                        RokitFlying.DCMove(stop, speed);
  }
}

