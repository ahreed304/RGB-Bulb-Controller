void transmitIRCommand(char payload[20])  
{
  for(int x = 0; x<sizeof(commandChar); x++) 
  {
    if(payload[node]==commandChar[x])  //if the payload contains a command for this node, send corresponding IR code
    {
      if(IRCodes[x]!=NULL)  {irsend.sendNEC(IRCodes[x], 32);}
      else
      {        
        switch(payload[node]) 
        {          
          case 'W': for(int y = 0; y<3; y++)  {irsend.sendNEC(IRCodes[18], 32);} //BRIGHTNESS 25%   -- brightness down(x3)
                    break;
          case 'X': for(int y = 0; y<3; y++)  {irsend.sendNEC(IRCodes[18], 32);} //BRIGHTNESS 50%   -- brightness down(x3), 
                    for(int y = 0; y<1; y++)  {irsend.sendNEC(IRCodes[17], 32);} //                 -- brightness up(x1)
                    break;
          case 'Y': for(int y = 0; y<3; y++)  {irsend.sendNEC(IRCodes[18], 32);} //BRIGHTNESS 75%   -- brightness down(x3),
                    for(int y = 0; y<2; y++)  {irsend.sendNEC(IRCodes[17], 32);} //                 -- brightness up(x2)
                    break;
          case 'Z': for(int y = 0; y<3; y++)  {irsend.sendNEC(IRCodes[17], 32);} //BRIGHTNESS 100%  -- brightness up(x3)
                    break;
        }//-----end switch
      }//-----end else
    }//-----end if
  }//-----end for
}//-----end method
  
