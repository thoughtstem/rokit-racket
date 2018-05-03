int sw  = 24;   //PA0 - switch
int led = 25;   //PA1 - led 

void setup()
{
  pinMode(sw, INPUT);
  digitalWrite(sw, HIGH);    //Pull up
  pinMode(led, OUTPUT);
}

void loop()
{
   int a = digitalRead(sw);
   if(a == 0) digitalWrite(led, HIGH);
   else digitalWrite(led, LOW); 
}
