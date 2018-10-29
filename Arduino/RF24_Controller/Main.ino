void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(pipeAddress[0]);
}//end setup

void loop()
{  
  if(Serial.available()) {
    dataIn = Serial.readString();
    len = dataIn.length()+1;
    char dataOut[len];
    dataIn.toCharArray(dataOut, len);
    isRepeatedCommand = false;
    
    switch(dataOut[10]) {
      case '0': radio.write(&dataOut, len);  
                Serial.println(dataOut);          break;
      case 'a': RainbowWave();                    break;
      case 'b': BackAndForth();                   break;
      case 'c': RandomColor();                    break;
      case 'd': RandomColorCycle();               break;
      default : radio.write(&dataOut, len);  
                Serial.println(dataOut);          break;
    }//end switch
    
    for(int x = 0; x<9 && isRepeatedCommand!=true; x++)
    {
      switch(dataOut[x])  {
        case '0': case '.':                       break;
        case 'A': case 'B': case 'C': case 'D': case 'E': 
        case 'F': case 'G': case 'H': case 'I': case 'J': 
        case 'K': case 'L': case 'P': case 'Q':
          isRepeatedCommand = true;               break;
        default: isRepeatedCommand = false;       break;
         
      }//end switch
    }//end for loop
    if(isRepeatedCommand==true)
    {
      for(int z = 0; z<5; z++)  {radio.write(&dataOut, len); Serial.println(dataOut);}
    }//end if statement
    
  }//end if statement
}//end loop
