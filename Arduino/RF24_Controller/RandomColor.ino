void RandomColor() {
    pattern[0] = color[random(0, 11)];
    pattern[1] = color[random(0, 11)];
    pattern[2] = color[random(0, 11)];
    pattern[3] = color[random(0, 11)];
    pattern[4] = color[random(0, 11)];
    pattern[5] = color[random(0, 11)];
    pattern[6] = color[random(0, 11)];
    pattern[7] = color[random(0, 11)];

    radio.write(pattern, 10);
}

void RandomColorCycle() {
  delayTime = 2500;
  while(Serial.available()==0) {
    RandomColor();
    delay(delayTime);
  }
}
