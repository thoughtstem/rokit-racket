/*****************************************************************
  ■ Dron 배터리 잔량 표시
  - 스마트 보드를 켜고 페어링 후 드론의 배터리를 보드의 led로 표현
*******************************************************************/

#include <SmartDroneControl.h>

//□ □ □ □ □ □ □ □
//11,12,13,14,15,16,17,18
int ledPins[] = { 11, 12, 13, 14, 15, 16, 17, 18 };
int pinCount = 8;

void setup()
{
  Serial.begin(9600);
  SmartDroneControl.begin();
  delay(500);

  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--)
  {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--)
  {
    digitalWrite(ledPins[thisPin], LOW);
  }
}

/***********************************************************/

void loop()
{
  SmartDroneControl.ResetYaw();
  SmartDroneControl.Receive();

  if (SUCESS_RECEIVE == true)
  {
    for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--)
    {
      digitalWrite(ledPins[thisPin], LOW);
    }

    int bt = Battery;

    //LED 로 배터리의 잔량 표시

    if (bt > 140) digitalWrite(18, HIGH);
    if (bt > 120) digitalWrite(17, HIGH);
    if (bt > 100) digitalWrite(16, HIGH);
    if (bt > 80)  digitalWrite(15, HIGH);
    if (bt > 60)  digitalWrite(14, HIGH);
    if (bt > 40)  digitalWrite(13, HIGH);
    if (bt > 20)  digitalWrite(12, HIGH);
    if (bt >= 0)  digitalWrite(11, HIGH);

    delay(100);
  }
}




