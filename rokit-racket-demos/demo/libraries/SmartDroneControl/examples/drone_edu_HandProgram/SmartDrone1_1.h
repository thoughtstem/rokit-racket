/*****************************************************************
■ 스마트 보드의 첫 번째 LED가 1초간격으로 점멸
*******************************************************************/

int ledPin = 11;              //8개 LED 중 첫 번째 핀설정 (변수 ledPin은 편의를 위해 만듬)

void SmartDrone1_1()
{
  pinMode(ledPin, OUTPUT);

  while (1)
  {
    digitalWrite(ledPin, HIGH); // 11번 led를 켠다
    delay(1000);
    digitalWrite(ledPin, LOW);  // 11번 led를 끈다
    delay(1000);
    //digitalWrite(11, HIGH);  변수를 사용하지 않고 핀번호 직접설정 가능
  }
}
