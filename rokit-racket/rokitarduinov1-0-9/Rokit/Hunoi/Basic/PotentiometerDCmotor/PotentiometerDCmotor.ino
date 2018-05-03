#include <MsTimer2.h>
#include <DCM.h>

int sen1,sen2;
int speed1,speed2;
DCM motor1;
DCM motor2;

void setup()
{
   motor1.attachPins(12, 13);
   motor2.attachPins(14, 15);
}

void loop()
{
    sen1 = analogRead(A0);
    sen2 = analogRead(A1);
    speed1 = map(sen1, 0, 1023, 0, 10);
    speed2 = map(sen2, 0, 1023, 0, 10);
    
    motor1.write(CW, speed1);
    motor2.write(CW, speed2);
    
}


