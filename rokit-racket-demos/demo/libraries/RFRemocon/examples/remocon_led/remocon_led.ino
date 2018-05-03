#include <RFRemocon.h>

#define LED1_PIN  16
#define LED2_PIN  17
#define LED3_PIN  18
#define LED4_PIN  19

void setup()
{
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  RFRemocon.begin(57600);
}

void loop()
{
  int data = RFRemocon.receive();
  if(data >= 0)
  {
    if(data & KEY_U)
      digitalWrite(LED1_PIN, HIGH);
    else
      digitalWrite(LED1_PIN, LOW);
      
    if(data & KEY_D)
      digitalWrite(LED2_PIN, HIGH);
    else
      digitalWrite(LED2_PIN, LOW);
      
    if(data & KEY_L)
      digitalWrite(LED3_PIN, HIGH);
    else
      digitalWrite(LED3_PIN, LOW);
      
    if(data & KEY_R)
      digitalWrite(LED4_PIN, HIGH);
    else
      digitalWrite(LED4_PIN, LOW);
  }
}
