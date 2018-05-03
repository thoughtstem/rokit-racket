/*****************************************************************
■  드론 호버링 제어
*******************************************************************/

#include <SmartDroneControl.h>  // 스마트 드론을 사용하기 위한 헤더파일 

int slowUp = 50;     // 천천히 올라가는 정도의 호버링값
int slowDown = -100;   // 천천히 내려가는 정도의 호버링값
int slowTime = 10;     // 천천히 움직이는 속도 조절 : 커지면 천천히 올라감.

void setup()
{
  Serial.begin(9600);   // 드론과 통신 개시 (9600bps)
  SmartDroneControl.begin();   // 드론 통신 개시
  delay(1000);

  // 밑면 센서 모두 입력으로 사용
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);
   SmartDroneControl.event = RESET_YAW;
    SmartDroneControl.Send();
    delay(1000);
}

void loop()
{
  byte bt1 = digitalRead(11);
  byte bt2 = digitalRead(12);
  byte bt3 = digitalRead(13);
  byte bt4 = digitalRead(14); //14 & 15
  byte bt6 = digitalRead(16);
  byte bt7 = digitalRead(17);
  byte bt8 = digitalRead(18);

  //*************************** Slow Up ***************************//
  //■ □ □ □ □ □ □   1 번째 센서에 손대면 천천히 상승
  if (bt8 && !bt7 && !bt6 && !bt4 && !bt3 && !bt2 && !bt1)
  {
    THROTTLE = slowUp;
    SmartDroneControl.Send();
    delay(slowTime);
    THROTTLE = 0;
    SmartDroneControl.Send();
  }

  //*************************** Slow Down ***************************//
  //□ □ □  □ □ □  ■   7 번째 센서에 손대면 천천히 하강
  else if (!bt8 && !bt7 && !bt6 && !bt4 && !bt3 && !bt2 && bt1)
  {
    THROTTLE = slowDown;
    SmartDroneControl.Send();
    delay(slowTime);
    THROTTLE = 0;
    SmartDroneControl.Send();
  }

  //**************************** STOP ******************************//
  //□ □ □  ■  □ □ □    밑몉 센서 4번째 감지시 Stop
  else if (bt4)
  {
    SmartDroneControl.Blink(80, 3);
    SmartDroneControl.LED(OFF);
    SmartDroneControl.Stop();
    SmartDroneControl.ButtonPreesHoldWait(14);  //button up
  }
  //**************************** TRIM ******************************//
  //□ ■ □ □ □ □ □  밑면 2 번째 센서 감지시 전진 Trim
  //Forward
  else if (!bt8 && bt7 && !bt6 && !bt4 && !bt3 && !bt2 && !bt1)
  {
    SmartDroneControl.TrimPitch(UP);
    SmartDroneControl.ButtonPreesHoldWait(17);  //button up
  }
  //□ □ □  □  □ ■ □  밑면 6 번째 센서 감지시 후진 Trim
  //Back
  else if (!bt8 && !bt7 && !bt6 && !bt4 && !bt3 && bt2 && !bt1)
  {
    SmartDroneControl.TrimPitch(DOWN);
    SmartDroneControl.ButtonPreesHoldWait(12);  //button up
  }
  //□ □ ■  □  □ □ □  밑면 1 번째 센서 감지시 왼쪽 Trim
  //Left
  else if (!bt8 && !bt7 && bt6 && !bt4 && !bt3 && !bt2 && !bt1)
  {
    SmartDroneControl.TrimRoll(UP);
    SmartDroneControl.ButtonPreesHoldWait(18);  //button up
  }
  //□ □ □  □  ■  □ □    밑면 7 번째 센서 감지시 오른쪽 Trim
  //Right
  else if (!bt8 && !bt7 && !bt6 && !bt4 && bt3 && !bt2 && !bt1)
  {
    SmartDroneControl.TrimRoll(DOWN);
    SmartDroneControl.ButtonPreesHoldWait(11);  //button up
  }
  delay(5);

}
