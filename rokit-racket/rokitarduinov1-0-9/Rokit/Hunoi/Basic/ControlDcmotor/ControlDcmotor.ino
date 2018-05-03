#include <Servo.h>
#include <MsTimer2.h>
#include <DCM.h>
#include <IRRemocon.h>

int Data = 0;
IRRemocon Remocon; 
DCM motor1;
DCM motor2;

void setup()
{
   Remocon.rokitSetup();
   Remocon.callback = remote;
   motor1.attachPins(12, 13);
   motor1.attachPins(14, 15);
  
}

void loop()
{
    Remocon.update();
    //you must not program here.  
}

void remote()
{
    Data = Remocon.read();
        
    if(Data == KEY_U)   {motor1.write(CW,10); motor2.write(CW,10);}
    else if(Data == KEY_D) {motor1.write(CCW, 10);motor2.write(CCW,10);} 
    else if(Data == KEY_L) {motor1.write(CCW,10);motor2.write(CW,10); }
    else if(Data == KEY_R) {motor1.write(CW,10);motor2.write(CCW,10); }
    else { motor1.write(STOP,10); motor2.write(STOP,10);}
 
}
