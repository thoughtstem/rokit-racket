#include <SmartInventor.h>

boolean left_line_sensor = false;
boolean right_line_sensor = true;
void setup(){
    SmartInventor.DCMotorUse();
    pinMode(13, INPUT);
    pinMode(16, INPUT);
}
void loop(){
    left_line_sensor = digitalRead(13);
    right_line_sensor = digitalRead(16);
    while(left_line_sensor == HIGH){
        SmartInventor.DCMotor(M1, CCW, 50);
        SmartInventor.DCMotor(M2, STOP, 0);
        left_line_sensor = digitalRead(13);
    }

    while(right_line_sensor == HIGH){
        SmartInventor.DCMotor(M1, STOP, 0);
        SmartInventor.DCMotor(M2, CW, 50);
        right_line_sensor = digitalRead(16);
    }

}