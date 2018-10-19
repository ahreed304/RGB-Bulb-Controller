
class Effects
{
  public:
    Effects(float delayTime);
    void RandomColor;
    void RainbowWave;
    void RandomColorCycle;

  private:
    bool _isForwards;
    float _multiplier, _multiplierForwards, _multiplierBackwards,
          _delayTime, _delayMin, _delayMax;
          _pattern, _color;
};

Effects::Effects(float delayTime) {
  _delayTime = delayTime;
} 

//============================================================================
void Effects::RandomColor() {
    _pattern[0] = _color[random(0, 11)];
    _pattern[1] = _color[random(0, 11)];
    _pattern[2] = _color[random(0, 11)];
    _pattern[3] = _color[random(0, 11)];
    _pattern[4] = _color[random(0, 11)];
    _pattern[5] = _color[random(0, 11)];
    _pattern[6] = _color[random(0, 11)];
    _pattern[7] = _color[random(0, 11)];

    radio.write(_pattern, 10);
}

void Effects::RandomColorCycle() {
  while(Serial.available()==0) {
    RandomColor();
    delay(_delayTime);
  }
}
}//============================================================================

void RainbowWave() {

    _delayTime = 500;
    _delayMin = 1;
    _delayMax = 1000;
    _multiplierForwards = .98;
    _multiplierBackwards = 1.02;
    _isForwards = true; 

    for(int x = 0; x<=9; x++) {
        pattern[x] = 0;
    }

    while (Serial.available()==0) {

        if(_isForwards==true) {multiplier = _multiplierForwards;}
        else {multiplier = _multiplierBackwards;}
        
        pattern[0] = color[next];
        _delayTime = _delayTime*multiplier;
        radio.write(pattern, 10); delay(_delayTime);
        pattern[1] = color[next];
        pattern[5] = color[next];
        _delayTime = _delayTime*multiplier;
        radio.write(pattern, 10); delay(_delayTime);
        pattern[2] = color[next];
        pattern[6] = color[next];
        _delayTime = _delayTime*multiplier;
        radio.write(pattern, 10); delay(_delayTime);
        pattern[3] = color[next];
        pattern[7] = color[next];
        pattern[8] = color[next];
        _delayTime = _delayTime*multiplier;
        radio.write(pattern, 10); delay(_delayTime*5);
        _delayTime = _delayTime*multiplier;

        if(next>=10) {next = 0;}
        else {next++;}

        if(_delayTime>=_delayMax) {_isForwards = true;}
        if(_delayTime<=_delayMin) {_isForwards = false;}
    }
}

//============================================================================================

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8); // CE, CSN 

const uint64_t pipeAddress[] = {0xF0F0F0F0AALL, 0xF0F0F0F066LL};
String dataIn;
int len;







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
        test.RandomColor();
      break;
      case 'b':
        
        break;
      case 'c':
        
      break;
    }
    radio.write(&dataOut, len);  
    Serial.println(dataOut);
  }  
}
