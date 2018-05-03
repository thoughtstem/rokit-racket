
int supportBaudList[] = {0x02, 0x03, 0x04, 0x07, 0x09, 0x10, 0x22};
long supportSpeedList[] = {666666, 500000, 400000, 250000, 200000, 115200, 57600};
int supportBaudNum = 7;

long BaudnumToSpeed(int baudnum)
{
  for(int i=0; i<supportBaudNum; i++)
  {
    if(supportBaudList[i] == baudnum)
      return supportSpeedList[i];
  }
  
  return 0;
}

void printIntro()
{
  Serial.println("Herkulex Manager");
  printPrompt();
}

void printPrompt()
{
  Serial.print("> ");
}

void printCmdError()
{
  Serial.println("Bad command. type 'help'");
  printPrompt();
}

void printMaxLengthError()
{
  Serial.println();
  Serial.println("Max command length");
  printPrompt();
}

void cmdHelp()
{
  Serial.println("========= Command ===========");
  Serial.println(" help");
  Serial.println(" scan");
  Serial.println(" search");
  Serial.println(" baud");  
  Serial.println(" baud [value]");  
  Serial.println(" id [value]");
  Serial.println(" go [id] [pos]");
  Serial.println(" read [id]");
  Serial.println("=============================");
  Serial.println();
  printPrompt();
}

void cmdBaud(char* arg)
{
  // display baudrate list
  Serial.println("===Support baurate list===");
  for(int i=0; i<supportBaudNum; i++)
  {
    Serial.print(supportBaudList[i], DEC);
    Serial.print("(");
    Serial.print(BaudnumToSpeed(supportBaudList[i]), DEC);
    Serial.println("bps)");
  }
  Serial.println("=======================");
  
  Serial.print("Current baud is ");
  Serial.print(baudNum, DEC);
  Serial.print("(");
  Serial.print(BaudnumToSpeed(baudNum), DEC);
  Serial.println("bps)");
  
  if(arg != 0)
  {
    int num = atoi(arg);
    Serial.print("New baud is ");
    if(BaudnumToSpeed(num) != 0)
    {
      baudNum = num;
      Herkulex.writeRegistryEEP(BROADCAST_ID, 4, baudNum);
      delay(500);
      Herkulex.reboot(BROADCAST_ID);
      Herkulex.end();
      Herkulex.beginSerial1(BaudnumToSpeed(baudNum)); 
      Serial.print(baudNum, DEC);
      Serial.print("(");
      Serial.print(BaudnumToSpeed(baudNum), DEC);
      Serial.println("bps)");
    }
    else
      Serial.println("invalid baud number");
  }
  
  printPrompt();
}

void cmdScan()
{
  int count = 0;
  Serial.println("Start scaning id...");
  for(int id=0; id<BROADCAST_ID; id++)
  {
    int err = Herkulex.stat(id);
    if(err >= 0)
    {
      Serial.print("[");
      Serial.print(id, DEC);
      Serial.print(": ");
      Serial.print(err, DEC);
      Serial.print("] ");
      count++;
      if(err > 0)
        Herkulex.clearError(id);
    }
  }
  Serial.println();
  Serial.print("Total found number is ");
  Serial.println(count, DEC);
  printPrompt();
}

void cmdSearch()
{
  int count = 0;
  int n = 0;
  boolean quit = false;
  Serial.println("Start searching... Press any key to quit");
  for(int i=0; i<supportBaudNum; i++)
  {
    Herkulex.beginSerial1(BaudnumToSpeed(supportBaudList[i])); 
    Serial.print("Baudrate: ");
    Serial.print(supportBaudList[i], DEC);
    Serial.print("(");
    Serial.print(BaudnumToSpeed(supportBaudList[i]), DEC);
    Serial.println("bps)");
    n = 0;
    for(int id=0; id<BROADCAST_ID; id++)
    {
      int err = Herkulex.stat(id);
      if(err >= 0)
      {
        Serial.print("[");
        Serial.print(id, DEC);
        Serial.print(": ");
        Serial.print(err, DEC);
        Serial.print("] ");
        n++;
        if(err > 0)
          Herkulex.clearError(id);
      }
     
      while(Serial.available() > 0)
      {
        Serial.read();
        quit = true;       
      }
      
      if(quit == true)
        break;
    }
    
    count += n;
    if(n > 0)
      Serial.println();
    
    if(quit == true)
    {
      Serial.println();
      Serial.print("Search canceled!");
      break;
    }
  }
  
  Herkulex.beginSerial1(BaudnumToSpeed(baudNum));
  Serial.println();
  Serial.print("Total found number is ");
  Serial.println(count, DEC);
  printPrompt();
}

void cmdGo(char* arg1, char* arg2)
{
  if(arg1 == 0)
    Serial.println("Invalid id");
  else
  {
    int id = atoi(arg1);
    if(arg2 == 0)
    {
      Herkulex.torqueON(BROADCAST_ID);
      Herkulex.moveOne(BROADCAST_ID, id, 1, 0);
    }
    else
    {
      int pos = atoi(arg2);
      Herkulex.torqueON(id);
      Herkulex.moveOne(id, pos, 1, 0);
    }
  }
  printPrompt();
}

void cmdID(char* arg1, char* arg2)
{
  if(arg1 == 0)
    Serial.println("Invalid id");
  else
  {
    int id = atoi(arg1);
    if(arg2 == 0)
      Serial.println("Invalid value");
    else
    {
      int value = atoi(arg2);
      if(value >= 0 && value < BROADCAST_ID)
      {
        Herkulex.set_ID(id, value);
        Herkulex.reboot(id);
      }
      else
        Serial.println("Invalid value");      
    }
  }
  printPrompt();
}

void cmdRead(char* arg1)
{
  if(arg1 == 0)
    Serial.println("Invalid id");
  else
  {
    int id = atoi(arg1);
    if(id >= 0 && id <= BROADCAST_ID)
    {
      int pos = Herkulex.getPosition(id);
      if(pos >= 0)
        Serial.println(pos, DEC);
    }
    else
      Serial.println("Invalid id");
  }
  printPrompt();
}

