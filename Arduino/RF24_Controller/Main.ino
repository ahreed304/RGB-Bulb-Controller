void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(pipeAddress[0]);
}

void loop() {  
  if(Serial.available()) {
    dataIn = Serial.readString();
    len = dataIn.length()+1;
    char dataOut[len];
    dataIn.toCharArray(dataOut, len);
    
    switch(dataOut[10]) {
      case 'a': RainbowWave();                    break;
      case 'b': RandomColor();                    break;
      case 'c': RandomColorCycle();               break;
      default : radio.write(&dataOut, len);  
                Serial.println(dataOut);          break;
    }
  }  
}
