#include <RokitFlying.h>

void Program_8()
{
  byte speed = 80;
  RokitFlying.TVRemoconUse();
  RokitFlying.DCMotorUse();

  Servo myservo1;
  myservo1.attach(6);
  myservo1.write(90);

  while (1)
  {
    int keyData =  RokitFlying.TVRemoconData();
    //Serial.println(keyData);

    if (keyData == KEY_U)       RokitFlying.DCMove(forward, speed);
    else if (keyData == KEY_D)  RokitFlying.DCMove(backward, speed);
    else if (keyData == KEY_L)  RokitFlying.DCMove(left_turn, speed);
    else if (keyData == KEY_R)  RokitFlying.DCMove(right_turn, speed);
    else                        RokitFlying.DCMove(stop, speed);

    if (keyData == KEY_F3)        myservo1.write(180);
    else if (keyData == KEY_F4)   myservo1.write(0);

  }
}

