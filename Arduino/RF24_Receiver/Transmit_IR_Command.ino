void transmitIRCommand()  
{
  for(int x = 0; x<sizeof(commandChar); x++) 
  {
    if(payload[node]==commandChar[x])
    {
      if(IRCodes[x]!=NULL)  {irsend.sendNEC(IRCodes[x], 32);}
      else
      {        
        switch(payload[node]) 
        {          
          case 'W': for(int y = 0; y<3; y++)  {irsend.sendNEC(IRCodes[16], 32);}
                    break;
          case 'X': for(int y = 0; y<3; y++)  {irsend.sendNEC(IRCodes[16], 32);}
                    for(int y = 0; y<1; y++)  {irsend.sendNEC(IRCodes[15], 32);}
                    break;
          case 'Y': for(int y = 0; y<3; y++)  {irsend.sendNEC(IRCodes[16], 32);}
                    for(int y = 0; y<2; y++)  {irsend.sendNEC(IRCodes[15], 32);}
                    break;
          case 'Z': for(int y = 0; y<3; y++)  {irsend.sendNEC(IRCodes[15], 32);}
                    break;
        }
      }
    } 
  }
}
  
