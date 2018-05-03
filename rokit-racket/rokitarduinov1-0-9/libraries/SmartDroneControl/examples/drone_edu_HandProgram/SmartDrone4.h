/*****************************************************************
■ 잠시 호버링하여 앞으로 전진하고 다시 착륙하는 구동
      주의사항 : 드론의 배터리에 따라 이동속도와 움직임이 달라지니
                 조금씩 파라미터와 delay값을 체크한다.
      1) 미션 1 :  앞으로 약 3미터 전진 이동후 착륙
      2) 미션 2 :  낭떠러지 1개 점프 후 착륙
      3) 미션 3 :  훌라후프와 같은 장애물 통과후 착륙
*******************************************************************/

#include <SmartDroneControl.h>   // 스마트 드론을 사용하기 위한 헤더파일 

void SmartDrone4()
{
  SmartDroneControl.begin();         // 드론 플러그의 기능 개시
  Serial.begin(9600);                  // 드론과 통신 개시(9600bps)
  delay(500);    // 명령후 잠시 대기

  SmartDroneControl.ResetYaw();     // 방향 설정, 비행 준비
  delay(1000);    // 명령후 잠시 대기

  THROTTLE  = 50;  // 50 정도로 위로 상승
  SmartDroneControl.Send();   // 명령 보냄
  delay(200);  // 0.2초정도 상승

  PITCH = 30;   // 30 정도로 앞으로 전진
  SmartDroneControl.Send();    // 명령 보냄
  delay(500);  // 0.5초정도 전진

  THROTTLE  = -50;    // -50 정도로 아래로 하강
  SmartDroneControl.Send();    // 명령 보냄
  delay(200); // 0.2초정도 상승

  SmartDroneControl.Stop();    // Stop 명령

  while (1);    //대기
}

