void RandomColor() //Assigns a random color to each bulb and broadcasts command
{
  int next, prev;
  char pattern[defaultCommandLength];
  memcpy(pattern, defaultCommand, defaultCommandLength);
  int patternLength = (sizeof(pattern));

  for(int x = 0; x <= patternLength-2; x++) {pattern[x] = color[random(1, 12)];}
  radio.write(pattern, patternLength);
  Serial.println(pattern);
}//-----end method RandomColor

void RandomColorCycle(float delayTime) //repeats RandomColor with a given time delay. repeats until new command is received from serial.  
{
  
  while(Serial.available()==0)
  {
    RandomColor();
    delay(delayTime);
  }//-----end while loop
}//-----end method RandomColorCycle
