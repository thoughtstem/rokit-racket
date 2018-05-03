/*****************************************************************
■ Trim (전후좌우로 흐르지 않는지 확인, 흐르면 Trim 셋팅)
두개의 조이스틱 중 analog3,4번핀의 조이스틱으로 높이를 조종하고
analog 5,6번 핀의 조이스틱으로 Trim을 셋팅한다.
*******************************************************************/

#include <SmartDroneControl.h>  // 스마트 드론 라이브러리를 포함해서 컴파일 

void SmartDrone2_2()
{
  int PreviousEventPitch = 0;   // Pitch의 이전 트림 버튼 상태값을 저장하기 위한 변수
  int PreviousEventYaw = 0;     // Yaw의 이전 트림 버튼 상태값을 저장하기 위한 변수
  int PreviousEventRoll = 0;    // Roll의 이전 트림 버튼 상태값을 저장하기 위한 변수

  SmartDroneControl.begin();         // 드론 플러그의 기능 개시
  Serial.begin(9600);                  // 드론과 통신 개시 (9600bps)
  delay(500);                           // 명령후 잠시 대기

  while (1)
  {
    byte bt1 = digitalRead(11);   // ■ □ □ □ □ □ □   밑면 적외선 센서
    byte bt4 = digitalRead(14);   // □ □ □ ■ □ □ □   밑면 적외선 센서
    byte bt8 = digitalRead(18);   // □ □ □ □ □ □ ■   밑면 적외선 센서

    // 조이스틱 2개를 연결후 Trim 진행
    int analogValue3 = analogRead(A3);  //yaw         좌  우
    int analogValue4 = analogRead(A4);  //throttle    위 아래
    int analogValue5 = analogRead(A5);  // roll         회전
    int analogValue6 = analogRead(A6);  //pitch       상  하


    //**************************** STOP ******************************//
    //   ■     □    □    □    □    □    □   밑면 첫 번째 센서 감지시 STOP
    //   bt1   bt2   bt3   bt4    bt6  bt7   bt8
    //   11    12   13   14 15   16  17    18
    if (bt1 && !bt4 && !bt8) //Stop
    {
      SmartDroneControl.Blink(80, 3);  // LED 상태 표시
      SmartDroneControl.LED(OFF);
      SmartDroneControl.Stop();    // Stop 명령
      SmartDroneControl.ButtonPreesHoldWait(11);  //button up
      STATE = READY;
    }

    //*************************** RESETYAW ***************************//
    //□ □ □ ■ ■ □ □ □    밑면 가 운 데 센서 감지시  방향 설정
    else if (bt4 && !bt1)  // RESETYAW (direction set) & flyingReady  무조건 시작시 감지시켜야함.
    {
      SmartDroneControl.Blink(80, 4);   // LED 상태 표시
      SmartDroneControl.LED(ON);
      SmartDroneControl.ResetYaw();    //
      SmartDroneControl.ButtonPreesHoldWait(14);  //button up
      STATE = FLY;
    }

    if (STATE == FLY)
    {
      THROTTLE  = SmartDroneControl.AnalogScaleChange(analogValue4);
      SmartDroneControl.IntervalSend(SEND_INTERVAL);    // throttle 값 보냄

      YAW = -1 * SmartDroneControl.AnalogScaleChange(analogValue3);
      ROLL = -1 * SmartDroneControl.AnalogScaleChange(analogValue5);
      PITCH = SmartDroneControl.AnalogScaleChange(analogValue6);

      // 값 초기화
      if (PITCH == 0) PreviousEventPitch = 0;
      if (ROLL == 0) PreviousEventRoll = 0;
      if (YAW == 0) PreviousEventYaw = 0;

      if (PITCH > 90) // 뒤로 가고 있으면 값 앞으로 Trim
      {
        if (TRIM_PITCH_INCREASE != PreviousEventPitch)
        {
          PreviousEventPitch = TRIM_PITCH_INCREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimPitch(UP);
        }
      }
      else if (PITCH < -90)  // 앞으로 가고 있으면 값 뒤로 Trim
      {
        if (TRIM_PITCH_DECREASE != PreviousEventPitch)
        {
          PreviousEventPitch = TRIM_PITCH_DECREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimPitch(DOWN);
        }
      }
      else if (ROLL > 90) // 왼쪽으로 이동하고 있으면 오른쪽으로 Trim
      {
        if (TRIM_ROLL_DECREASE != PreviousEventRoll)
        {
          PreviousEventRoll = TRIM_ROLL_DECREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimRoll(DOWN);
        }
      }
      else if (ROLL < -90)  // 오른쪽으로 이동하고 있으면 왼쪽으로 Trim
      {
        if (TRIM_ROLL_INCREASE != PreviousEventRoll)
        {
          PreviousEventRoll = TRIM_ROLL_INCREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimRoll(UP);
        }
      }
      else if (YAW > 90)  // 왼쪽으로 회전시 오른쪽으로 회전 Trim
      {
        if (TRIM_YAW_INCREASE != PreviousEventYaw)
        {
          PreviousEventYaw = TRIM_YAW_INCREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimYaw(UP);
        }
      }
      else if (YAW < -90) // 오른쪽으로 회전시 왼쪽으로 회전 Trim
      {
        if (TRIM_YAW_DECREASE != PreviousEventYaw)
        {
          PreviousEventYaw = TRIM_YAW_DECREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimYaw(DOWN);
        }
      }
      THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;  //받은 센서 값을 초기화
    }
  }
}
