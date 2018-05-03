#include <RokitFlying.h>

//WiredRemocon Control
void setup()
{
  RokitFlying.WiredRemoconUse();  // Wired Remocon Use
  Serial.begin(57600);          // initialize serial communication at 57600 bits per second:
  delay(500);                    // waits 500ms
}

void loop()
{
  int keyData =  RokitFlying.WiredRemocon();  // read Wired Remocon receive data => keyData

  if (keyData == KEY_U)                   // read Wired Remocon receive data then 'KEY_U'
  {
    Serial.println("Forward");           // receive data print
  }
  else if (keyData == KEY_D)              // read Wired Remocon receive data then 'KEY_D'
  {
    Serial.println("Backword");          // receive data print
  }
  else if (keyData == KEY_L)              // read Wired Remocon receive data then 'KEY_L'
  {
    Serial.println("Left");              // receive data print
  }
  else if (keyData == KEY_R)              // read Wired Remocon receive data then 'KEY_R'
  {
    Serial.println("Right");             // receive data print
  }
  else if (keyData == KEY_F1)             // read Wired Remocon receive data then 'KEY_F1'
  {
    Serial.println("F1");                // receive data print
  }
  else if (keyData == KEY_F2)             // read Wired Remocon receive data then 'KEY_F2'
  {
    Serial.println("F2");                // receive data print
  }
}









