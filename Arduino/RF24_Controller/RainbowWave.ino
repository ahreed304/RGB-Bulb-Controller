void RainbowWave()
{

  delayTime = 500;
  delayMin = 1;
  delayMax = 1000;
  multiplierFaster = .98;
  multiplierSlower = 1.02;
  isFaster = true;
  isForwardColor = random(0,2);
  next = random(1, 12); 

  for(int x = 0; x<sizeof(pattern); x++) {pattern[x] = 0;}
  if(isForward == true) {isForward = false;}  else  {isForward = true;}

  while (Serial.available()==0)
  {
    if(isForward == true) {ForwardWave();}
    else  {BackwardWave();}
      
  }
}//end method

void ForwardWave()  
{
  if(isFaster==true) {multiplier = multiplierFaster;}
  else {multiplier = multiplierSlower;}
        
  pattern[0] = color[next];
  radio.write(pattern, sizeof(pattern)); delay(delayTime);
  delayTime = delayTime*multiplier;

  pattern[1] = color[next];
  pattern[5] = color[next];
  radio.write(pattern, sizeof(pattern)); delay(delayTime);
  delayTime = delayTime*multiplier;

  pattern[2] = color[next];
  pattern[6] = color[next];
  pattern[8] = color[next];
  radio.write(pattern, sizeof(pattern)); delay(delayTime);
  delayTime = delayTime*multiplier;

  pattern[3] = color[next];
  pattern[7] = color[next];
  radio.write(pattern, sizeof(pattern)); delay(delayTime*5);
  delayTime = delayTime*multiplier;

  if (isForwardColor==true)
  {
    if(next>=11) {next = 1;}
    else {next++;}
  }
  else
  {
    if(next<=1) {next = 11;}
    else {next--;}
  }

  if(delayTime>=delayMax) {isFaster = true;}
  if(delayTime<=delayMin) {isFaster = false;}
}//end method

void BackwardWave()  
{
  if(isFaster==true) {multiplier = multiplierFaster;}
  else {multiplier = multiplierSlower;}

  pattern[3] = color[next];
  pattern[7] = color[next];
  radio.write(pattern, sizeof(pattern)); delay(delayTime);
  delayTime = delayTime*multiplier;

  pattern[2] = color[next];
  pattern[6] = color[next];
  pattern[8] = color[next];
  radio.write(pattern, sizeof(pattern)); delay(delayTime);
  delayTime = delayTime*multiplier;

  pattern[1] = color[next];
  pattern[5] = color[next];
  radio.write(pattern, sizeof(pattern)); delay(delayTime);
  delayTime = delayTime*multiplier;
        
  pattern[0] = color[next];
  radio.write(pattern, sizeof(pattern)); delay(delayTime*5);
  delayTime = delayTime*multiplier;

  if (isForwardColor==true)
  {
    if(next>=11) {next = 1;}
    else {next++;}
  }
  else
  {
    if(next<=1) {next = 11;}
    else {next--;}
  }

  if(delayTime>=delayMax) {isFaster = true;}
  if(delayTime<=delayMin) {isFaster = false;}
}//end method

void BackAndForth()
{
  delayTime = 500;
  delayMin = 1;
  delayMax = 1000;
  multiplierFaster = .98;
  multiplierSlower = 1.02;
  isFaster = true;
  next = random(1, 12);
  for(int x = 0; x<sizeof(pattern); x++) {pattern[x] = 0;}
   
  while(Serial.available()==0)
  {
    if(isFaster==true) {multiplier = multiplierFaster;}
    else {multiplier = multiplierSlower;}

    pattern[0] = color[next];
    radio.write(pattern, sizeof(pattern)); delay(delayTime);
    delayTime = delayTime*multiplier;

    pattern[1] = color[next];
    pattern[5] = color[next];
    radio.write(pattern, sizeof(pattern)); delay(delayTime);
    delayTime = delayTime*multiplier;

    pattern[2] = color[next];
    pattern[6] = color[next];
    pattern[8] = color[next];
    radio.write(pattern, sizeof(pattern)); delay(delayTime);
    delayTime = delayTime*multiplier;

    pattern[3] = color[next];
    pattern[7] = color[next];
    radio.write(pattern, sizeof(pattern)); delay(delayTime*5);
    delayTime = delayTime*multiplier;

    prev = next;
    while(next==prev) {next = random(1, 12);}
    for(int x = 0; x<sizeof(pattern); x++) {pattern[x] = 0;} 


    pattern[3] = color[next];
    pattern[7] = color[next];
    radio.write(pattern, sizeof(pattern)); delay(delayTime);
    delayTime = delayTime*multiplier;

    pattern[2] = color[next];
    pattern[6] = color[next];
    pattern[8] = color[next];
    radio.write(pattern, sizeof(pattern)); delay(delayTime);
    delayTime = delayTime*multiplier;

    pattern[1] = color[next];
    pattern[5] = color[next];
    radio.write(pattern, sizeof(pattern)); delay(delayTime);
    delayTime = delayTime*multiplier;

    pattern[0] = color[next];
    radio.write(pattern, sizeof(pattern)); delay(delayTime*5);
    delayTime = delayTime*multiplier;

    prev = next;
    while(next==prev) {next = random(1, 12);}
    for(int x = 0; x<sizeof(pattern); x++) {pattern[x] = 0;}


    if(delayTime>=delayMax) {isFaster = true;}
    if(delayTime<=delayMin) {isFaster = false;}
  }
}//end method
