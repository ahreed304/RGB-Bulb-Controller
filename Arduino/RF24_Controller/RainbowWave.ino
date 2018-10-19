void RainbowWave() {

    delayTime = 500;
    delayMin = 1;
    delayMax = 1000;
    multiplierForwards = .98;
    multiplierBackwards = 1.02;
    isForwards = true;
    next = random(0, 11); 

    for(int x = 0; x<sizeof(pattern); x++) {
        pattern[x] = 0;
    }

    while (Serial.available()==0) {

        if(isForwards==true) {multiplier = multiplierForwards;}
        else {multiplier = multiplierBackwards;}
        
        pattern[0] = color[next];
        delayTime = delayTime*multiplier;
        radio.write(pattern, 10); delay(delayTime);
        pattern[1] = color[next];
        pattern[5] = color[next];
        delayTime = delayTime*multiplier;
        radio.write(pattern, 10); delay(delayTime);
        pattern[2] = color[next];
        pattern[6] = color[next];
        delayTime = delayTime*multiplier;
        radio.write(pattern, 10); delay(delayTime);
        pattern[3] = color[next];
        pattern[7] = color[next];
        pattern[8] = color[next];
        delayTime = delayTime*multiplier;
        radio.write(pattern, 10); delay(delayTime*5);
        delayTime = delayTime*multiplier;

        if(next>=10) {next = 0;}
        else {next++;}

        if(delayTime>=delayMax) {isForwards = true;}
        if(delayTime<=delayMin) {isForwards = false;}
    }
}
