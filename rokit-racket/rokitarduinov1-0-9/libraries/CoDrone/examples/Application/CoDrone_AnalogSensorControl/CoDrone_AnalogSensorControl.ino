/******************************************************************************************************
  - Analog Sensor Control
  아날로그 센서3개와 디지털센서 3개를 이용한 조종 예제
  인벤터 보드 전방의 아날로그 센서 3개와 바닥의 디지털 센서 3개를 조합하여 드론을 조종합니다.
  
  누르는 버튼에 따라 아날로그 센서의 용도가 달라집니다.
        
  ■ □ □ □ □ □ □  bt1을 누르면 정지
  
  □ □ □ ■ □ □ □  bt4를 누르고 있을 때   
  A1 - 높이 조절
  A0 - 좌이동
  A2 - 우이동
        
  □ □ □ □ □ □ ■  bt8을 누르고 있을 때 
  A1 - 높이 조절
  A0 - 전진
  A2 - 후진
  
******************************************************************************************************/

#include <CoDrone.h> // 코드론을 사용하기 위한 헤더파일 

void setup()
{  
  CoDrone.begin(115200);                // 드론 플러그의 통신 개시 (115200bps)

  CoDrone.AutoConnect(NearbyDrone);     // 가장 가까운 위치의 드론과 연결

  CoDrone.DroneModeChange(Flight);       // 드론을 플라이트 모드로 설정합니다. (비행형)
}

void loop()
{
  byte bt1 = digitalRead(11);       // ■ □ □ □ □ □ □   밑면 적외선 센서를 입력으로 사용
  byte bt4 = digitalRead(14);       // □ □ □ ■ □ □ □   밑면 적외선 센서를 입력으로 사용
  byte bt8 = digitalRead(18);       // □ □ □ □ □ □ ■   밑면 적외선 센서를 입력으로 사용
  
  int analogValue0 = analogRead(A0);  // 자기가 원하는 것과 연결가능
  int analogValue1 = analogRead(A1);  // 자기가 원하는 것과 연결가능
  int analogValue2 = analogRead(A2);  // 자기가 원하는 것과 연결가능
  
  if (bt1 && !bt4 && !bt8)           // 밑면 센서 가장 끝 1번센서에 손을 대면 실행합니다.
  {
    CoDrone.FlightEvent(Stop);      // 드론을 정지시킵니다.
   //  CoDrone.FlightEvent(Landing);      // 드론을 정지시킵니다.
  }

  if (bt4)       // 밑면 센서  4번센서에 손을 대면 실행합니다.             
  {
    THROTTLE  = map(analogValue1, 0, 1023, -50, 200);  // 승하강
    ROLL = map(analogValue0, 0, 1023, 100, 0) + map(analogValue2, 0, 1023, -100, 0);      //  좌우이동
    CoDrone.Control(SEND_INTERVAL);                         // 제어 신호를 보냅니다. 통신이 안정하게 가도록 시간을 두고 보냄(최소 50ms)
  }
  
  if (bt8)       // 밑면 센서 가장 끝 7번센서에 손을 대면 실행합니다.
  {
    THROTTLE  = map(analogValue1, 0, 1023, -50, 200);  // 승하강
    PITCH = map(analogValue0, 0, 1023, -100, 0) + map(analogValue2, 0, 1023, 100, 0);     //  전후진
    CoDrone.Control(SEND_INTERVAL);                         // 제어 신호를 보냅니다. 통신이 안정하게 가도록 시간을 두고 보냄(최소 50ms)
  }
}


