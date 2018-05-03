/*****************************************************************
■ 드론 리모트 콘트롤 소스
*******************************************************************/

#include <SmartDroneControl.h>  // 스마트 드론을 사용하기 위한 헤더파일 

void SmartDrone5()
{
  int PreviousEventPitch = 0; // Pitch의 이전 트림 버튼 상태값을 저장하기 위한 변수
  int PreviousEventYaw = 0;   // Yaw의 이전 트림 버튼 상태값을 저장하기 위한 변수
  int PreviousEventRoll = 0;  // Roll의 이전 트림 버튼 상태값을 저장하기 위한 변수

  Serial.begin(9600);                 // 시리얼 통신(무선통신) 개시
  SmartDroneControl.begin();         // 드론 플러그의 기능 개시
  delay(1000);

  /***********************************************************/

  while (1)
  {
    byte dipBt1 = digitalRead(8);    // 딥스위치 1번 상태 체크
    byte dipBt2 = digitalRead(9);    // 딥스위치 2번 상태 체크
    byte dipBt3 = digitalRead(10);    // 딥스위치 3번 상태 체크

    byte bt1 = digitalRead(11);       // ■ □ □ □ □ □ □   밑면 적외선 센서
    byte bt4 = digitalRead(14);       // □ □ □ ■ □ □ □   밑면 적외선 센서
    byte bt8 = digitalRead(18);       // □ □ □ □ □ □ ■   밑면 적외선 센서

    int analogValue3 = analogRead(A3);  //yaw         좌  우
    int analogValue4 = analogRead(A4);  //throttle    위 아래
    int analogValue5 = analogRead(A5);  //roll        회전
    int analogValue6 = analogRead(A6);  //pitch       상  하

    //*************************** PAIRING *****************************//
    // |_-_| Dip Switch2 UP 딥스위치의 2번만 올리면 페어링
    if (dipBt1 == HIGH && dipBt2 == LOW && dipBt3 == HIGH)  //PAIRING
    {
      STATE = READY;
      SmartDroneControl.Pairing();       // 페어링 명령
      delay(1500);

      // LED 퍼포먼스

      digitalWrite(13, HIGH);
      digitalWrite(16, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      digitalWrite(16, LOW);
      delay(100);
      digitalWrite(12, HIGH);
      digitalWrite(17, HIGH);
      delay(100);
      digitalWrite(12, LOW);
      digitalWrite(17, LOW);
      delay(100);
    }



    //**************************** STOP ******************************//
    //   ■     □    □    □    □    □    □   밑면 첫 번째 센서 감지시 STOP
    //   bt1   bt2   bt3   bt4    bt6  bt7   bt8
    //   11    12   13   14 15   16  17    18
    else if (bt1 && !bt4 && !bt8) //Stop
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

    //*************************** Trim Reset ***********************//
    //■ □ □ □ □ □ □ ■
    else if (bt8 && bt1 && !bt4)  //Trim Reset
    {
      SmartDroneControl.Blink(50, 3);   // LED 상태 표시
      SmartDroneControl.LED(ON);
      digitalWrite(17, HIGH);
      SmartDroneControl.TrimReset();
      SmartDroneControl.ButtonPreesHoldWait(11, 18); //button up
    }

    //*************************** TrimMode Set ***********************//
    //□ □ □ □ □ □ □ ■
    if (bt8)  //TrimMode Set    // 밑면 센서 가장 끝 8번센서 손대고 있으면 TrimMode 진입
    {
      if (STATE == FLY) STATE = TRIM;
    }
    else if (!bt8)  //TrimMode Set
    {
      if (STATE == TRIM) STATE = FLY;
    }

    //*************************** FLY CONTROL ***********************//
    if (STATE == FLY)   // 현재 공중에 날고 있는 상태 체크
    {
      YAW = -1 * SmartDroneControl.AnalogScaleChange(analogValue3); // 상하
      THROTTLE  = SmartDroneControl.AnalogScaleChange(analogValue4); // 좌우
      ROLL = -1 * SmartDroneControl.AnalogScaleChange(analogValue5); // 전후
      PITCH = SmartDroneControl.AnalogScaleChange(analogValue6); // 회전
      SmartDroneControl.IntervalSend(SEND_INTERVAL); // 통신이 안정하게 가도록 인터벌 시간두고 보냄
    }

    //*************************** TRIM CONTROL ***********************//
    else if (STATE == TRIM)
    {
      //       +        +
      //      3, 4       5,6
      YAW = -1 * SmartDroneControl.AnalogScaleChange(analogValue3);
      ROLL = -1 * SmartDroneControl.AnalogScaleChange(analogValue5);
      PITCH = SmartDroneControl.AnalogScaleChange(analogValue6);

      if (PITCH == 0) PreviousEventPitch = 0;
      if (ROLL == 0) PreviousEventRoll = 0;
      if (YAW == 0) PreviousEventYaw = 0;

      if (PITCH > 90) // 전진
      {
        if (TRIM_PITCH_INCREASE != PreviousEventPitch)
        {
          PreviousEventPitch = TRIM_PITCH_INCREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimPitch(UP);
        }
      }
      else if (PITCH < -90)  // 후진
      {
        if (TRIM_PITCH_DECREASE != PreviousEventPitch)
        {
          PreviousEventPitch = TRIM_PITCH_DECREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimPitch(DOWN);
        }
      }
      else if (ROLL > 90) // 우이동
      {
        if (TRIM_ROLL_DECREASE != PreviousEventRoll)
        {
          PreviousEventRoll = TRIM_ROLL_DECREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimRoll(DOWN);
        }
      }
      else if (ROLL < -90)  // 좌이동
      {
        if (TRIM_ROLL_INCREASE != PreviousEventRoll)
        {
          PreviousEventRoll = TRIM_ROLL_INCREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimRoll(UP);
        }
      }
      else if (YAW > 90)  // 우회전
      {
        if (TRIM_YAW_INCREASE != PreviousEventYaw)
        {
          PreviousEventYaw = TRIM_YAW_INCREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimYaw(UP);
        }
      }
      else if (YAW < -90) //좌회전
      {
        if (TRIM_YAW_DECREASE != PreviousEventYaw)
        {
          PreviousEventYaw = TRIM_YAW_DECREASE;
          THROTTLE = 0;            PITCH = 0;            ROLL = 0;            YAW = 0;
          SmartDroneControl.TrimYaw(DOWN);
        }
      }
    }
  }
}
