#include <SmartInventor.h>

boolean leftSensor = false;
boolean rightSensor = false;
int moveSpeed = 50;
void setup(){
    SmartInventor.DCMotorUse();
    pinMode(11, INPUT);
    pinMode(18, INPUT);
}
void wiggle_attack(){
    SmartInventor.DCMove(forward, moveSpeed);
    delay(1000);
    SmartInventor.DCMove(left, moveSpeed);
    delay(500);
    SmartInventor.DCMove(right, moveSpeed);
    delay(500);
    SmartInventor.DCMove(left, moveSpeed);
    delay(500);
    SmartInventor.DCMove(right, moveSpeed);
    delay(500);
    SmartInventor.DCMove(left, moveSpeed);
    delay(500);
    SmartInventor.DCMove(right, moveSpeed);
    delay(500);
    SmartInventor.DCMove(left, moveSpeed);
    delay(500);
    SmartInventor.DCMove(right, moveSpeed);
    delay(500);
    SmartInventor.DCMove(left, moveSpeed);
    delay(500);
    SmartInventor.DCMove(right, moveSpeed);
    delay(500);
}
void spin_attack(){
    SmartInventor.DCMove(forward, moveSpeed);
    delay(1000);
    SmartInventor.DCMotor(M1, CW, moveSpeed);
    SmartInventor.DCMotor(M2, CW, moveSpeed);
    delay(4000);
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
    leftSensor = digitalRead(11);
    rightSensor = digitalRead(18);
    if(leftSensor == false){
        backup_and_turn_right();
        wiggle_attack();}
    else if(rightSensor == false){
        backup_and_turn_left();
        spin_attack();
    }
    else{
        go_forward();
    }
}