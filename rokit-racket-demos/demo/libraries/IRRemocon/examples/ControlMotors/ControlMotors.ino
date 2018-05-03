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
   Remocon.attachCallback(remote);
   motor1.attachPins(12, 13);
   motor2.attachPins(14, 15); 
}

void loop()
{
    Remocon.update();
    //you must not program here.  
}

void remote()
{
    Data = Remocon.read();
        
    if(Data == 1)  {motor1.write(CCW,10); motor2.write(CCW, 10);}
    else if(Data == 2) {motor1.write(CW, 10); motor2.write(CW,10);} 
    else if(Data == 4) {motor1.write(CCW,10); motor2.write(CW,10); }
    else if(Data == 8) {motor1.write(CW,10); motor2.write(CCW,10); }
    else { motor1.write(LOOSE,10); motor2.write(LOOSE,10);}
 
}
