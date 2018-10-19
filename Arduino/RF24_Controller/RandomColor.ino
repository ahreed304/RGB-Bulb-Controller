void RandomColor() {
  for(int x = 0; x<sizeof(pattern); x++) {pattern[x] = color[random(0, 11)];}
  radio.write(pattern, 10);
}

void RandomColorCycle() {
  delayTime = 2500;
  while(Serial.available()==0) {
    RandomColor();
    delay(delayTime);
  }
}
