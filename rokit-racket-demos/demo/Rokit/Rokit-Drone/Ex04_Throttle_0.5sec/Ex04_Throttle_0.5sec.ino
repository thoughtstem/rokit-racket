/*****************************************************************
  ■ Drone을 0.5 초간 상승시키고 손으로 받기
  - 여기서부터는 프로그래밍시 반드시 'Reset Yaw'와 'Stop'이 있어야한다
*******************************************************************/
#include <SmartDroneControl.h>  // 스마트 드론을 사용하기 위한 헤더파일 

void setup()
{
  Serial.begin(9600);                 // 시리얼 통신(무선통신) 개시
  SmartDroneControl.begin();        // 드론 플러그의 기능 개시
  delay(1000);

  SmartDroneControl.ResetYaw();     // 0.5초간 ResetYaw 필수
  delay(500);

  THROTTLE = 50;                        // 50의 상승 속도 
  SmartDroneControl.Send();

  delay(500);                           // 약 0.5초간만

  SmartDroneControl.Stop();          // 정지
}

void loop()
{
  //아래의 내용은 실시간으로 계속 제어보드의 센서값을 체크한다.
  byte dipBt1 = digitalRead(8);    // 딥스위치 1번 상태 체크
  byte dipBt2 = digitalRead(9);    // 딥스위치 2번 상태 체크
  byte dipBt3 = digitalRead(10);    // 딥스위치 3번 상태 체크

  byte bt1 = digitalRead(11);       // ■ □ □ □ □ □ □   밑면 적외선 센서
  byte bt4 = digitalRead(14);       // □ □ □ ■ □ □ □   밑면 적외선 센서
  byte bt8 = digitalRead(18);       // □ □ □ □ □ □ ■   밑면 적외선 센서

  int analogValue0 = analogRead(A0);  // 자기가 원하는 것과 연결가능
  int analogValue1 = analogRead(A1);  // 자기가 원하는 것과 연결가능
  int analogValue2 = analogRead(A2);  // 자기가 원하는 것과 연결가능
  int analogValue3 = analogRead(A3);  //pitch       상  하
  int analogValue4 = analogRead(A4);  //yaw         좌  우
  int analogValue5 = analogRead(A5);  //throttle    위 아래
  int analogValue6 = analogRead(A6);  //roll        회전

  ///////////////////////////◆프로그램부분◆///////////////////////////////




  ////////////////////////////////////////////////////////////////////////////

}

