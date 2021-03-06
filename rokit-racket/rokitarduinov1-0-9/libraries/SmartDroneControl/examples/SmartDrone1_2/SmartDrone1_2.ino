/*****************************************************************
■ 밑면의 센서 감지시 LED 8번째 켜지는 구동
주의사항 : 밑면 센서와 LED는 연동되어있어서 같은 핀은 센서감지시
LED 자동으로 켜짐.
(센서와 LED중 한가지만 택일하여 사용할 수 있음)
*******************************************************************/

void setup() 
{
  pinMode(11, INPUT);               // 보드 밑면 첫 번째 센서를 입력
  pinMode(18, OUTPUT);              // 보드 윗면 제일 끝 LED를 출력설정
}

void loop() 
{
  if(digitalRead(11) == HIGH)       // 밑면 첫 번째 센서가 감지되면
  {      
    digitalWrite(18, HIGH);         // 윗면 마지막 LED가 On
  } 
  else                              // 밑면 첫 번째 센서가 감지되지않으면
  {
    digitalWrite(18, LOW);          // 윗면 마지막 LED가 On
  }
}
