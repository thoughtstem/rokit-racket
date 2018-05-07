#include <SmartInventor.h>

boolean left_sensor = false;
boolean right_sensor = false;
void setup(){
    SmartInventor.DCMotorUse();
    pinMode(11, INPUT);
    pinMode(18, INPUT);
}
void backup_and_turn_right(){
    SmartInventor.DCMotor(M1, CW, 50);
    SmartInventor.DCMotor(M2, CCW, 50);
    delay(333);
    SmartInventor.DCMotor(M1, CCW, 50);
    SmartInventor.DCMotor(M2, CCW, 50);
    delay(333);
}
void backup_and_turn_left(){
    SmartInventor.DCMotor(M1, CW, 50);
    SmartInventor.DCMotor(M2, CCW, 50);
    delay(333);
    SmartInventor.DCMotor(M1, CW, 50);
    SmartInventor.DCMotor(M2, CW, 50);
    delay(333);
}
void go_forward(){
    SmartInventor.DCMotor(M1, CCW, 50);
    SmartInventor.DCMotor(M2, CW, 50);
}
void loop(){
    left_sensor = digitalRead(11);
    right_sensor = digitalRead(18);
    if(left_sensor == false){
        backup_and_turn_right();}
    else if(right_sensor == false){
        backup_and_turn_left();
    }
    else{
        go_forward();
    }
}