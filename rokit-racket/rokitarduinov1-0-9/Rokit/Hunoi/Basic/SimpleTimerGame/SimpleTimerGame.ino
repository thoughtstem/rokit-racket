int sw  = 24;   //PA0 - switch
int randNumber;

void setup()
{
   Serial.begin(9600);
   pinMode(sw, INPUT);
   digitalWrite(sw, HIGH);    //Pull up
   randomSeed(analogRead(A0));

}

void loop()
{
   
   randNumber = 5 + random(10);
   Serial.println("Let's start game!");
   Serial.print("You must push button in ");
   Serial.print(randNumber);
   Serial.println(" seconds accurately!");
   delay(3000);  
   
   while(1)
  { 
     int a = digitalRead(sw);
     Serial.println(millis());
     if(a == 0) {delay(3000); break;}
  }  
}
