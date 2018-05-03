
void printIntro()
{
  Serial.println("Dynamixel Manager");
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
  Serial.println(" write [id] [addr] [value] [length]");
  Serial.println(" read [id] [addr] [length]");
  Serial.println("=============================");
  Serial.println();
  printPrompt();
}

void cmdBaud(char* arg)
{
  Serial.print("Current baud is ");
  Serial.print(baudNum, DEC);
  Serial.print("(");
  Serial.print(Dynamixel.baudnumToSpeed(baudNum), DEC);
  Serial.println("bps)");
  
  if(arg != 0)
  {
    int num = atoi(arg);
    Serial.print("New baud is ");
    if(num >= 0 && num < 255)
    {
      baudNum = num;
      Dynamixel.write(BROADCAST_ID, 4, (byte)baudNum);
      Dynamixel.begin(Dynamixel.baudnumToSpeed(baudNum));   
      Serial.print(baudNum, DEC);
      Serial.print("(");
      Serial.print(Dynamixel.baudnumToSpeed(baudNum), DEC);
      Serial.println("bps)");
    }
    else
      Serial.println("invalid");
  }
  
  printPrompt();
}

void cmdScan()
{
  int count = 0;
  Serial.println("Start scaning id...");
  for(int id=0; id<BROADCAST_ID; id++)
  {
    if(Dynamixel.ping(id) == COMMERROR_NONE)
    {
      Serial.print("[");
      Serial.print(id, DEC);
      Serial.print("] ");
      count++;
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
  for(int baud=0; baud<255; baud++)
  {
    Dynamixel.begin(Dynamixel.baudnumToSpeed(baud));
    Serial.print("Baudrate: ");
    Serial.print(baud, DEC);
    Serial.print("(");
    Serial.print(Dynamixel.baudnumToSpeed(baud), DEC);
    Serial.println("bps)");
    n = 0;
    for(int id=0; id<BROADCAST_ID; id++)
    {
      if(Dynamixel.ping(id) == COMMERROR_NONE)
      {
        Serial.print("[");
        Serial.print(id, DEC);
        Serial.print("] ");
        n++;
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
      Serial.println("Invalid position");
    else
    {
      int pos = atoi(arg2);
      Dynamixel.joint(id, (word)pos);
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
        Dynamixel.write(id, 3, (byte)value);
      }
      else
        Serial.println("Invalid value");      
    }
  }
  printPrompt();
}

void cmdWrite(char* arg1, char* arg2, char* arg3, char* arg4)
{
  if(arg1 == 0)
    Serial.println("Invalid id");
  else
  {
    int id = atoi(arg1);
    if(id >= 0 && id <= BROADCAST_ID)
    {
      if(arg2 == 0)
        Serial.println("Invalid address");
      else
      {
        int addr = atoi(arg2);
        if(addr >= 0 && addr < 256)
        {
          if(arg3 == 0)
            Serial.println("Invalid value");
          else
          {
            int value = atoi(arg3);
            if(arg4 == 0)
              Serial.println("Invalid length");
            else
            {
              int length = atoi(arg4);
              if(length == 1)
              {
                Dynamixel.write(id, addr, (byte)value);
              }
              else if(length == 2)
              {
                Dynamixel.write(id, addr, (word)value);
              }
              else
                Serial.println("Invalid length");
            }
          }
        }
        else
          Serial.println("Invalid address");
      }
    }
    else
      Serial.println("Invalid id");
  }
  printPrompt();
}

void cmdRead(char* arg1, char* arg2, char* arg3)
{
  byte bValue;
  word wValue;
  
  if(arg1 == 0)
    Serial.println("Invalid id");
  else
  {
    int id = atoi(arg1);
    if(id >= 0 && id <= BROADCAST_ID)
    {
      if(arg2 == 0)
        Serial.println("Invalid address");
      else
      {
        int addr = atoi(arg2);
        if(addr >= 0 && addr < 256)
        {
          if(arg3 == 0)
            Serial.println("Invalid length");
          else
          {
            int length = atoi(arg3);
            if(length == 1)
            {
              if(Dynamixel.read(id, addr, &bValue) == COMMERROR_NONE)
                Serial.println(bValue, DEC);
            }
            else if(length == 2)
            {
              if(Dynamixel.read(id, addr, &wValue) == COMMERROR_NONE)
                Serial.println(wValue, DEC);
            }
            else
              Serial.println("Invalid length");    
          }
        }
        else
          Serial.println("Invalid address");
      }
    }
    else
      Serial.println("Invalid id");
  }
  printPrompt();
}
