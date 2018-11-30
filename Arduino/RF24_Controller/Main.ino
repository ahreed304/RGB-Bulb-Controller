void setup()
{ 
  //Initial setup for radio and serial connections
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(pipeAddress[0]);
}//-----end setup

void loop()
{
  String payloadIn;
  int payloadLength;
  
  //Listen for incoming command from Raspberry Pi via USB serial port   
  if(Serial.available()) 
  {
    //Store received command as string called "payloadIn"
    String payloadIn = Serial.readString();

    //Convert command to char array to be broadcast via radio
    payloadLength = payloadIn.length()+1;
    char payloadOut[payloadLength];
    payloadIn.toCharArray(payloadOut, payloadLength);
    Serial.print("payloadOut = ");
    Serial.print(payloadOut); //print payloadOut for debugging purposes
    

    //if command calls for dynamic color-changing effect, execute associated function
    switch(payloadOut[10]) {
      case '0': default :
        radio.write(&payloadOut, payloadLength);  
        Serial.println(payloadOut);                 break;        //default action is to simply broadcast payload
        
      case 'a': RainbowWave();                      return; break;  //sweeping rainbow lighting pattern
      case 'b': BackAndForth();                     return; break;  //alternative sweeping lighting pattern
      case 'c': RandomColor();                      return; break;  //random color for each light
      case 'd': RandomColorCycle(2500);             return; break;  //random color for each light every 2.5 seconds
    }//-----end switch

    //Many commands may be transmitted multiple times to increase chance of successful reception by all receivers
    bool isRepeatedCommand = false;
    
    //examine command to see if it should be repeated
    for(int x = 0; (x <= defaultCommandLength-2) && (isRepeatedCommand != true); x++)
    {
      switch(payloadOut[x])  {
        case '0': case '.':                       break;
        
        case 'A': case 'B': case 'C': case 'D': case 'E': 
        case 'F': case 'G': case 'H': case 'I': case 'J': 
        case 'K': case 'L': case 'P': case 'Q':
          isRepeatedCommand = true;               break;
          
        default: isRepeatedCommand = false;       break;
      }//-----end switch
    }//-----end for loop

    //repeat broadcast 4 additional times if applicable
    if(isRepeatedCommand == true)
    {
      for(int z = 0; z < 4; z++)  
      {
        delay(100);
        radio.write(&payloadOut, payloadLength); 
        Serial.println(payloadOut);
        }//-----end for
    }//-----end if
    
  }//-----end if
}//-----end loop
