//Motor A
int PWMA = 16; //Speed control 
int AIN1 = 8; //Direction1
int AIN2 = 9; //Direction2

//Motor B
int PWMB = 18; //Speed control
int BIN1 = 10; //Direction1
int BIN2 = 11; //Direction2

//motor control
const int analogInSpeedPin = A0;  //Speed Input
const int DirectionPin = 15;      //Direction Input
int sensorValue = 0;              // value read from the pot
int SpeedValue = 0;               // speed scale change

void setup(){
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(DirectionPin, INPUT_PULLUP);
}

void loop()
{
  sensorValue = analogRead(analogInSpeedPin);           
  SpeedValue = map(sensorValue, 0, 1023, 0, 255);  

  if (digitalRead(DirectionPin) == LOW) {
    move(1, SpeedValue, 0); //motor A, speed, CCW
    move(2, SpeedValue, 0); //motor B, speed, CCW
  } 
  else {
    move(1, SpeedValue, 1); //motor A, speed, CW
    move(2, SpeedValue, 1); //motor B, speed, CW
  }
}


void move(int motor, int speed, int direction)
{
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }
  else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

