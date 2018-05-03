/*****************************************************************
  ■ 부메랑 턴
  - 유저의 손에서 오른쪽으로 돌기시작하여 왼쪽으로 원을 그리며 돌아오는 드론 구동
  - 부메랑 처럼 돌아오는 드론  리셋버튼누를때마다 재실행
  <주의 사항>
  1. 드론의 배터리에 따라 값이 달라질수 있다.
  2. 드론의 새기체냐 오래사용된 기체이냐에 따라 값이 달라질수 있다.
*******************************************************************/
#include <SmartDroneControl.h>      // 스마트 드론을 사용하기 위한 헤더파일 

void setup()
{
  SmartDroneControl.begin();         // 드론 플러그의 기능 개시
  Serial.begin(9600);                  // 드론과 통신 개시(9600bps)
  delay(500);                           // 명령후 잠시 대기

  SmartDroneControl.ResetYaw();      // 방향 설정, 비행 준비
  delay(1000);                          // 명령후 잠시 대기

  int nFlight = 40;
  int nTime = 700;  //짧게 V_TURN 500  ~ 길게 V_TURN 1000

  // 드론자체가 새기체일때
  /*
    SendDrone(40,nFlight,nFlight,0,nTime);
    SendDrone(-20,nFlight,-nFlight,0,nTime*1.2);
    SendDrone(-20,-nFlight,-nFlight,0,nTime*1.4);
    SendDrone(-20,-nFlight,nFlight,0,nTime*1.8);
  */
  // 드론자체가 사용하던 기체일때

  SendDrone(40, nFlight, nFlight, 0, nTime);
  SendDrone(40, nFlight, -nFlight, 0, nTime * 1.2);
  SendDrone(40, -nFlight, -nFlight, 0, nTime * 1.4);
  SendDrone(40, -nFlight, nFlight, 0, nTime * 1.8);

  SmartDroneControl.Stop();    // Stop 명령
}

void loop()
{


}

void SendDrone(int a, int b, int c, int d, int nDelay)
{
  THROTTLE = a;
  PITCH = b;
  ROLL = c;
  YAW = d;
  SmartDroneControl.Send();    // Stop 명령
  delay(nDelay);
}
