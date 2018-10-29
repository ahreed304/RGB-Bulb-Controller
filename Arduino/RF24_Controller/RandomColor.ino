void RandomColor() 
{
  for(int x = 0; x<sizeof(pattern); x++) {pattern[x] = color[random(1, 12)];}
  radio.write(pattern, sizeof(pattern));
}//end method

void RandomColorCycle()
{
  delayTime = 2500;  
  
  while(Serial.available()==0)
  {
    RandomColor();
    delay(delayTime);
  }//end while loop
}//end method
