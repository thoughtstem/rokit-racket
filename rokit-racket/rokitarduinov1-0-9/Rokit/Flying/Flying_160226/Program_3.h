#include <RokitFlying.h>
#include <Servo.h>

void Program_3()
{
  byte speed = 80;

  RokitFlying.WiredRemoconUse();
  RokitFlying.DCMotorUse();

  Servo myservo1;
  myservo1.attach(6);
  myservo1.write(90);

  while (1)
  {
    int keyData = RokitFlying.WiredRemocon();
    // Serial.println(keyData);
    
    if (keyData == KEY_U)       RokitFlying.DCMove(forward, speed);
    else if (keyData == KEY_D)  RokitFlying.DCMove(backward, speed);
    else if (keyData == KEY_L)  RokitFlying.DCMove(left, speed);
    else if (keyData == KEY_R)  RokitFlying.DCMove(right, speed);
    else                        RokitFlying.DCMove(stop, speed);

    if (keyData == KEY_F1)        myservo1.write(0);
    else if (keyData == KEY_F2)   myservo1.write(180);
  }
}

