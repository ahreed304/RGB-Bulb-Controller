//This code controls my television and stereo using the same equipment and processes as the the RGB light bulbs.
//Programmed commands include: volume up, volume down, mute, power, input source, etc.  Any function may be programmed.  
//Any device with an IR remote can be controlled using this system

//Code is fully-functional but in a very early version
//Comments will be added when code is refactored

#include <SPI.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

IRsend irsend;
RF24 radio(7, 8); // CE, CSN


const int node = 11;  //THIS NODE'S NUMBER
const int node2 = 12;

const uint64_t pipeAddress[] = {0xF0F0F0F0AALL, 0xF0F0F0F066LL};
const int len = 20;  //ADDRESS STRING LENGTH
char dataIn[20];
int x, y;

const int tPin1 = 4;
const int tPin2 = 5;
int tPin1State = LOW;
int tPin2State = LOW;

void setup() {
  Serial.begin(9600);
  printf_begin();
  
  radio.begin();
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1, pipeAddress[0]);
  radio.startListening();

  pinMode(tPin1, OUTPUT);
  pinMode(tPin2, OUTPUT);
}

void loop() {
  tPin1State = HIGH; 
    digitalWrite(tPin1, tPin1State);
  if(radio.available(1)) {
    radio.read(&dataIn, len);
    Serial.println(dataIn);

    

    /*
    if(dataIn[node]=='0') {
      tPin1State = LOW; digitalWrite(tPin1, tPin1State);
    } else tPin1State = HIGH; digitalWrite(tPin1, tPin1State);
    if(dataIn[node2]=='0') {
      tPin2State = LOW; digitalWrite(tPin2, tPin2State);
    } else tPin2State = HIGH; digitalWrite(tPin2, tPin2State);
    */
    
    
    if(dataIn[node]!='0') {
      tPin1State = HIGH;
      digitalWrite(tPin1, tPin1State);
      tPin2State = LOW;
      digitalWrite(tPin2, tPin2State);
    }
    else if(dataIn[node2]!='0') {
      tPin1State = LOW;
      digitalWrite(tPin1, tPin1State);
      tPin2State = HIGH;
      digitalWrite(tPin2, tPin2State);
    }
    
    

    /*
    switch(dataIn[node]) {
      case '0': tPin1State = HIGH; digitalWrite(tPin1, tPin1State);
                tPin2State = LOW;  digitalWrite(tPin2, tPin2State);    
                break;
      default : tPin1State = LOW; digitalWrite(tPin1, tPin1State);
                tPin2State = LOW;  digitalWrite(tPin2, tPin2State);
                break;   
    }
    switch(dataIn[node2]) {
      case '0': tPin1State = LOW; digitalWrite(tPin1, tPin1State);
                tPin2State = HIGH;  digitalWrite(tPin2, tPin2State);    
                break;
      default : tPin1State = LOW; digitalWrite(tPin1, tPin1State);
                tPin2State = LOW;  digitalWrite(tPin2, tPin2State);
                break;   
    }
    */
    
    //=========================TV================================
    switch(dataIn[node]) {
      case '0': break;
      case 'a':
        for(y = 0; y<3; y++) {irsend.sendSony(0xA90, 12);} 
        break;  //POWER
      case 'b': 
        for(x = 0; x<5; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0xC90, 12);}
          delay(150);
        } 
        break;  //VOLUME DOWN
      case 'c': 
        for(x = 0; x<10; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0xC90, 12);}
          delay(150);
        } 
        break;  //VOLUME DOWN 2
      case 'd': 
        for(x = 0; x<20; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0xC90, 12);}
          delay(150);
        } 
        break;  //VOLUME DOWN 3
      case 'e': 
        for(x = 0; x<5; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0x490, 12);}
          delay(150);
        } 
        break;  //VOLUME UP
      case 'f': 
        for(x = 0; x<10; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0x490, 12);}
          delay(150);
        } 
        break;  //VOLUME UP 2
      case 'g': 
        for(x = 0; x<20; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0x490, 12);}
          delay(150);
        } 
        break;  //VOLUME UP 3
      case 'h': 
        for(y = 0; y<3; y++) {irsend.sendSony(0x290, 12);}
        break;  //MUTE
      case 'i':
        for(y = 0; y<3; y++) {irsend.sendSony(0xA50, 12);}
        delay(500);
        for(x = 0; x<6; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0xAF0, 12);}
          delay(150);
        }
        for(x = 0; x<2; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0x2F0, 12);}
          delay(150);
        }
        for(y = 0; y<3; y++) {irsend.sendSony(0xA70, 12);}  
        break;  //HDMI 1
      case 'j':
        for(y = 0; y<3; y++) {irsend.sendSony(0xA50, 12);}
        delay(500);
        for(x = 0; x<6; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0xAF0, 12);}
          delay(150);
        }
        for(y = 0; y<3; y++) {irsend.sendSony(0x2F0, 12);}
        delay(150);
        for(y = 0; y<3; y++) {irsend.sendSony(0xA70, 12);}  
        break;  //HDMI 2
      case 'k':
        for(y = 0; y<3; y++) {irsend.sendSony(0xA50, 12);}
        delay(500);
        for(x = 0; x<6; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0xAF0, 12);}
          delay(150);
        }
        for(y = 0; y<3; y++) {irsend.sendSony(0xA70, 12);}  
        break;  //HDMI 3
    }
    //=========================END TV================================
    
    //=========================STEREO================================
    switch(dataIn[node2]) {
      case '0': break;
      case 'a': 
        for(y = 0; y<3; y++) {irsend.sendSony(0xA81, 12); delay(40);} 
        break;  //POWER
      case 'b': 
        for(y = 0; y<3; y++) {irsend.sendSony(0xC81, 12); delay(40);}
        break;  //VOLUME DOWN
      case 'c': 
        for(x = 0; x<3; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0xC81, 12); delay(40);}
          delay(150);
        } 
        break;  //VOLUME DOWN 2
      case 'd': 
        for(x = 0; x<5; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0xC81, 12); delay(40);}
          delay(150);
        } 
        break;  //VOLUME DOWN 3
      case 'e': 
        for(y = 0; y<3; y++) {irsend.sendSony(0x481, 12); delay(40);}
        break;  //VOLUME UP
      case 'f': 
        for(x = 0; x<3; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0x481, 12); delay(40);}
          delay(150);
        } 
        break;  //VOLUME UP 2
      case 'g': 
        for(x = 0; x<5; x++) {
          for(y = 0; y<3; y++) {irsend.sendSony(0x481, 12); delay(40);}
          delay(150);
        } 
        break;  //VOLUME UP 3
      case 'h': 
        for(y = 0; y<3; y++) {irsend.sendSony(0x281, 12); delay(40);}
        break;  //MUTE
    }
    //=========================END STEREO================================
    tPin1State = LOW; digitalWrite(tPin1, tPin1State);
    tPin2State = LOW; digitalWrite(tPin2, tPin2State);      
  }
 }
