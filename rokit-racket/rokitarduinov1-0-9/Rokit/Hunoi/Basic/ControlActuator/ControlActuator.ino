#include <Servo.h>
#include <MsTimer2.h>
#include <DCM.h>
#include <IRRemocon.h>

int Data = 0;
IRRemocon Remocon; 
DCM motor1;
Servo servo1;

void setup()
{
   Remocon.rokitSetup();
   Remocon.callback = remote;
   motor1.attachPins(14, 15);
   servo1.attach(31);  
   servo1.write(90);
}

void loop()
{
    Remocon.update();
    //you must not program here.  
}

void remote()
{
    Data = Remocon.read();
        
    if(Data == 1)   {motor1.write(CCW,10);}
    else if(Data == 2) {motor1.write(CW, 10);} 
    else if(Data == 4) {servo1.write(179); delay(100); }
    else if(Data == 8) {servo1.write(0); delay(100); }
    else { motor1.write(LOOSE,10); servo1.write(90);}
 
}
