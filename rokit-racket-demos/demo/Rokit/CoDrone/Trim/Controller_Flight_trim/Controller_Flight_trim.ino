/*****************************************************************
  Trim - Analog Joystick Control + Trim
  - 드론을 조이스틱으로 조종합니다.
  스마트 보드를 조종기 형태로 조립해서 사용하는 예제입니다.
  밑면 센서 가장 끝 1번센서에 손을 대면 드론이 정지하게 됩니다.

-드론이 한쪽으로 치우치거나 출력의 제어가 안되는 경우에는 트림 기능을 사용하여 보정합니다.

밑면 센서 가장 끝 8번 센서에 손을 댄 상태에서 조종기를 움직이게 되면 해당방향에 보정값이 입력됩니다.
원하는 방향의 반대쪽으로 트림값을 입력하면 됩니다.
한번 스틱을 움직일때마다 1씩 값이 보정되므로, 값을 크게 변경하고 싶다면 여러번 스틱을 움직여야 합니다.

ex) 드론이 너무 상승한다면, 센서 8번에 손을 댄체로 조이스틱을 아래방향으로 여러번 연속으로 내리도록 합니다.

-밑면 센서 가장 끝 8번과 1번을 동시에 누르게 되면, 트림 값이 초기화 (0) 됩니다.
    
*******************************************************************/

int PreviousEventPitch = 0;
int PreviousEventThrottle = 0;
int PreviousEventYaw = 0;
int PreviousEventRoll = 0;

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
  
  if (PAIRING == true)                // 연결(페어링)이 성공한 경우에만 실행
  {

    //**************************** STOP ******************************//
    //■ □ □ □ □ □ □ □
    if (bt1 && !bt4 && !bt8)           // 밑면 센서 가장 끝 1번센서에 손을 대면 실행합니다.
    {
      CoDrone.FlightEvent(Stop);      // 드론을 정지시킵니다.
      // CoDrone.FlightEvent(Landing);      // 드론을 정지시킵니다.
    }

    //*************************** Trim Reset ***********************//
    //■ □ □ □ □ □ □ ■
    else if (bt1 && !bt4 && bt8)  //Trim Reset
    {
      CoDrone.Set_TrimReset();
      CoDrone.LED_Blink(25, 5);
      CoDrone.LED_Connect();
      CoDrone.ButtonPreesHoldWait(11, 18); //button up
    }

    //*************************** Control & Trim  ***********************//
    //□ □ □ □ □ □ □ ■
    if (!bt8)  //Control Mode Set
    {
      digitalWrite(16, HIGH);
      YAW = -1 * CoDrone.AnalogScaleChange(analogRead(A3));   // 아날로그 3번 핀의 값을 YAW 값으로 사용합니다.       - 좌우회전
      THROTTLE  = CoDrone.AnalogScaleChange(analogRead(A4));  // 아날로그 4번 핀의 값을 THROTTLE 값으로 사용합니다.  - 승하강
      ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(A5));  // 아날로그 5번 핀의 값을 ROLL 값으로 사용합니다.      - 좌우이동
      PITCH = CoDrone.AnalogScaleChange(analogRead(A6));      // 아날로그 6번 핀의 값을 PITCH 값으로 사용합니다.     - 전후진
      CoDrone.Control(SEND_INTERVAL);                         // 제어 신호를 보냅니다. 통신이 안정하게 가도록 시간을 두고 보냄(최소 50ms)
    }

    else if (bt8)  //Trim Mode Set
    {
      digitalWrite(16, LOW);
      YAW = -1 * CoDrone.AnalogScaleChange(analogRead(A3));
      THROTTLE  = CoDrone.AnalogScaleChange(analogRead(A4));
      ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(A5));
      PITCH = CoDrone.AnalogScaleChange(analogRead(A6));

      if (PITCH == 0) PreviousEventPitch = 0;
      if (THROTTLE == 0) PreviousEventThrottle = 0;
      if (ROLL == 0) PreviousEventRoll = 0;
      if (YAW == 0) PreviousEventYaw = 0;

      if ((PITCH != 0) || (THROTTLE != 0) || (ROLL != 0) || (YAW != 0))
      {
            CoDrone.LED_Blink(20, 3);
            CoDrone.LED_Connect();
            digitalWrite(16, LOW);
      }

      if (PITCH > 90)
      {
        if (PreviousEventPitch != PitchIncrease)
        {
          PreviousEventPitch = PitchIncrease;
          CoDrone.Set_Trim(PitchIncrease);
        }
      }

      else if (PITCH < -90)
      {
        if (PreviousEventPitch != PitchDecrease)
        {
          PreviousEventPitch = PitchDecrease;
          CoDrone.Set_Trim(PitchDecrease);
        }
      }

      else if (THROTTLE > 90)
      {
        if (PreviousEventThrottle != trim_ThrottleIncrease)
        {
          PreviousEventThrottle = trim_ThrottleIncrease;
          CoDrone.Set_Trim(trim_ThrottleIncrease);
        }
      }

      else if (THROTTLE < -90)
      {
        if (PreviousEventThrottle != trim_ThrottleDecrease)
        {
          PreviousEventThrottle = trim_ThrottleDecrease;
          CoDrone.Set_Trim(trim_ThrottleDecrease);
        }
      }

      else if (ROLL > 90)
      {
        if (PreviousEventRoll != RollDecrease)
        {
          PreviousEventRoll = RollDecrease;
          CoDrone.Set_Trim(RollDecrease);
        }
      }
      else if (ROLL < -90)
      {
        if (PreviousEventRoll != RollIncrease)
        {
          PreviousEventRoll = RollIncrease;
          CoDrone.Set_Trim(RollIncrease);
        }
      }

      else if (YAW > 90)
      {
        if (PreviousEventYaw != YawIncrease)
        {
          PreviousEventYaw = YawIncrease;
          CoDrone.Set_Trim(YawIncrease);
        }
      }
      else if (YAW < -90)
      {
        if (PreviousEventYaw != YawDecrease)
        {
          PreviousEventYaw = YawDecrease;
          CoDrone.Set_Trim(YawDecrease);
        }
      }
    }
  }
}




