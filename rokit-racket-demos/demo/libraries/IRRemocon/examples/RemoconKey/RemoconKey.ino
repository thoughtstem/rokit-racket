#include <IRRemocon.h>

int Data = 0;
IRRemocon Remocon; ;

void setup()
{
   Serial.begin(9600);
   Remocon.rokitSetup();
   Remocon.attachCallback(remote);
}

void loop()
{
    Remocon.update();
    //you must not program here.  
}

void remote()
{
    Data = Remocon.read();
        
    if(Data == KEY_U)  Serial.println("You pushed UP key.");  
    else if(Data == KEY_D) Serial.println("You pushed DOWN key."); 
    else if(Data == KEY_L) Serial.println("You pushed LEFT key."); 
    else if(Data == KEY_R) Serial.println("You pushed RIGHT key.");
    
}
