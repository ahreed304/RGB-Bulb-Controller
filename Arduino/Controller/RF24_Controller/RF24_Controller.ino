#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8); // CE, CSN 

const uint64_t pipeAddress[] = {0xF0F0F0F0AALL, 0xF0F0F0F066LL};
String dataIn;
int len;

bool isForwards;
float multiplier, multiplierForwards, multiplierBackwards;

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
      case 'a':
        RainbowWave();   
      break;
      case 'b':
        RainbowWave3();
        break;
      case 'c': 
      break;
    }
    radio.write(&dataOut, len);  
    Serial.println(dataOut);
  }  
}