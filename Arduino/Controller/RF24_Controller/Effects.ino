

void RainbowWave() {
  float delayTime, delayMin, delayMax;
  
  delayTime = 500;
  delayMin = 1;
  delayMax = 1000;
  multiplierForwards = .98;
  multiplierBackwards = 1.02;
  isForwards = true; 
  while(Serial.available()==0) {
    if(isForwards==true) {multiplier = multiplierForwards;} else {multiplier = multiplierBackwards;}
    while(delayTime>=delayMin && delayTime<=delayMax && Serial.available()==0) {
      if(Serial.available()==0) {
        radio.write("B000.0000", 10); delay(delayTime);
        radio.write("BB00.0000", 10); delay(delayTime);
        radio.write("BBB0.0B0B", 10); delay(delayTime);
        radio.write("BBBB.BBBB", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
      if(Serial.available()==0) {
        radio.write("L000.0000", 10); delay(delayTime);
        radio.write("LL00.0000", 10); delay(delayTime);
        radio.write("LLL0.0L0L", 10); delay(delayTime);
        radio.write("LLLL.LLLL", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
      if(Serial.available()==0) {
        radio.write("K000.0000", 10); delay(delayTime);
        radio.write("KK00.0000", 10); delay(delayTime);
        radio.write("KKK0.0K0K", 10); delay(delayTime);
        radio.write("KKKK.KKKK", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
      if(Serial.available()==0) {
        radio.write("J000.0000", 10); delay(delayTime);
        radio.write("JJ00.0000", 10); delay(delayTime);
        radio.write("JJJ0.0J0J", 10); delay(delayTime);
        radio.write("JJJJ.JJJJ", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
      if(Serial.available()==0) {
        radio.write("I000.0000", 10); delay(delayTime);
        radio.write("II00.0000", 10); delay(delayTime);
        radio.write("III0.0I0I", 10); delay(delayTime);
        radio.write("IIII.IIII", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
      if(Serial.available()==0) {
        radio.write("H000.0000", 10); delay(delayTime);
        radio.write("HH00.0000", 10); delay(delayTime);
        radio.write("HHH0.0H0H", 10); delay(delayTime);
        radio.write("HHHH.HHHH", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
      if(Serial.available()==0) {
        radio.write("G000.0000", 10); delay(delayTime);
        radio.write("GG00.0000", 10); delay(delayTime);
        radio.write("GGG0.0G0G", 10); delay(delayTime);
        radio.write("GGGG.GGGG", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
      if(Serial.available()==0) {
        radio.write("F000.0000", 10); delay(delayTime);
        radio.write("FF00.0000", 10); delay(delayTime);
        radio.write("FFF0.0F0F", 10); delay(delayTime);
        radio.write("FFFF.FFFF", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
      if(Serial.available()==0) {
        radio.write("E000.0000", 10); delay(delayTime);
        radio.write("EE00.0000", 10); delay(delayTime);
        radio.write("EEE0.0E0E", 10); delay(delayTime);
        radio.write("EEEE.EEEE", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
      if(Serial.available()==0) {
        radio.write("D000.0000", 10); delay(delayTime);
        radio.write("DD00.0000", 10); delay(delayTime);
        radio.write("DDD0.0D0D", 10); delay(delayTime);
        radio.write("DDDD.DDDD", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
      if(Serial.available()==0) {
        radio.write("C000.0000", 10); delay(delayTime);
        radio.write("CC00.0000", 10); delay(delayTime);
        radio.write("CCC0.0C0C", 10); delay(delayTime);
        radio.write("CCCC.CCCC", 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;
      }
    }
    if(isForwards==true) {isForwards = false; delayTime = delayMin;} else {isForwards = true; delayTime = delayMax;}
  }
}
