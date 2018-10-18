#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <IRremote.h>

IRsend irsend;
RF24 radio(7, 8); // CE, CSN


const int node = 5;  //THIS NODE'S NUMBER

const uint64_t pipeAddress[] = {0xF0F0F0F0AALL, 0xF0F0F0F066LL};
const int len = 20;  //ADDRESS STRING LENGTH
char dataIn[20];

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1, pipeAddress[0]);
  radio.startListening();
}

void loop() {
  if(radio.available(1)) {
    radio.read(&dataIn, len);
    switch(dataIn[node]) {
      //=============================COLORS==============================
      case '0': break;
      case 'A': irsend.sendNEC(0xFF52AD, 32); break;  //WHITE
      case 'B': irsend.sendNEC(0xFF6897, 32); break;  //RED
      case 'C': irsend.sendNEC(0xFF30CF, 32); break;  //ORANGE
      case 'D': irsend.sendNEC(0xFF38C7, 32); break;  //GOLD
      case 'E': irsend.sendNEC(0xFF4AB5, 32); break;  //YELLOW
      case 'F': irsend.sendNEC(0xFF9867, 32); break;  //GREEN
      case 'G': irsend.sendNEC(0xFF18E7, 32); break;  //TEAL
      case 'H': irsend.sendNEC(0xFF5AA5, 32); break;  //CYAN
      case 'I': irsend.sendNEC(0xFFB04F, 32); break;  //BLUE
      case 'J': irsend.sendNEC(0xFF7A85, 32); break;  //PURPLE
      case 'K': irsend.sendNEC(0xFF10EF, 32); break;  //MAGENTA
      case 'L': irsend.sendNEC(0xFF42BD, 32); break;  //PINK
      //===========================END COLORS============================
      //===========================FUNCTIONS=============================
      case 'P': irsend.sendNEC(0xFFA25D, 32); break;  //ON
      case 'Q': irsend.sendNEC(0xFFE21D, 32); break;  //OFF
      case 'R': irsend.sendNEC(0xFFA857, 32); break;  //BRIGHTER
      case 'S': irsend.sendNEC(0xFF906F, 32); break;  //DIMMER
      case 'T': irsend.sendNEC(0xFF22DD, 32); break;  //FLASH (LAVENDER)
      case 'U': irsend.sendNEC(0xFFE01F, 32); break;  //SMOOTH (CRIMSON)
      case 'V': irsend.sendNEC(0xFF629D, 32); break;  //SPEED (INDIGO)
      case 'W': irsend.sendNEC(0xFF906F, 32);
                irsend.sendNEC(0xFF906F, 32);
                irsend.sendNEC(0xFF906F, 32); break;  //BRIGHTNESS 25%
      case 'X': irsend.sendNEC(0xFF906F, 32);
                irsend.sendNEC(0xFF906F, 32);
                irsend.sendNEC(0xFF906F, 32);
                irsend.sendNEC(0xFFA857, 32); break;  //BRIGHTNESS 50%
      case 'Y': irsend.sendNEC(0xFF906F, 32);
                irsend.sendNEC(0xFF906F, 32);
                irsend.sendNEC(0xFF906F, 32);
                irsend.sendNEC(0xFFA857, 32);
                irsend.sendNEC(0xFFA857, 32); break;  //BRIGHTNESS 75%
      case 'Z': irsend.sendNEC(0xFFA857, 32);
                irsend.sendNEC(0xFFA857, 32);
                irsend.sendNEC(0xFFA857, 32); break;  //BRIGHTNESS 100%       
      //=========================END FUNCTIONS===========================
    }        
  }
}
