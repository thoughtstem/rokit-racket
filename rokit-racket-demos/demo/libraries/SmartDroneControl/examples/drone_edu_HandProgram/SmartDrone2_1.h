/*****************************************************************
■ 다음 소스만으로 페어링 구동을 확인하자.
*******************************************************************/

#include <SmartDroneControl.h> // 스마트 드론을 사용하기 위한 헤더파일 

void SmartDrone2_1()
{
  SmartDroneControl.begin();         // 드론 플러그의 기능 개시
  Serial.begin(9600);                  // 드론과 통신 개시(9600bps)
  delay(500);                           // 명령후 잠시 대기

  while (1)
  {
    SmartDroneControl.Pairing();       // 페어링 명령
    delay(2000);                          // 2초 정지
  }
}
