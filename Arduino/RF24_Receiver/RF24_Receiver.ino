//include RF24 libraries for NRF24L01 radio transceiver
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

//include IRemote library for IR LED
#include <IRremote.h>

IRsend irsend; //create object for IRremote
RF24 radio(7, 8); // create RF24 object (CE, CSN pin numbers chosen on Arduino)

// \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ 
const int node = 5;  //THIS NODE'S NUMBER
// /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ 

const uint64_t pipeAddress[] = {0xF0F0F0F0AALL, 0xF0F0F0F066LL};  //Addresses used for radio connections.  Only the first one is used as of now.  


//The following arrays match each possible char in a payload to a specific command and a corresponding IR code. 
//array value =             0         1         2         3         4         5         6         7         8         9         10        11        12        13        14        15        16        17        18        19                20                21              22              23              24              25
const long IRCodes[] =     {0xFF52AD, 0xFF6897, 0xFF30CF, 0xFF38C7, 0xFF4AB5, 0xFF9867, 0xFF18E7, 0xFF5AA5, 0xFFB04F, 0xFF7A85, 0xFF10EF, 0xFF42BD, NULL,     NULL,     NULL,     0xFFA25D, 0xFFE21D, 0xFFA857, 0xFF906F, 0xFF22DD,         0xFFE01F,         0xFF629D,       NULL,           NULL,           NULL,           NULL};
//command =                 WHITE     RED       ORANGE    GOLD      YELLOW    GREEN     TURQUOISE CYAN      BLUE      PURPLE    MAGENTA   PINK      NULL      NULL      NULL      ON        OFF       BRIGHTER  DIMMER    FLASH (LAVENDER)  SMOOTH (CRIMSON)  SPEED (INDIGO)  BRIGHTNESS 25%  BRIGHTNESS 50%  BRIGHTNESS 75%  BRIGHTNESS 100%
const char commandChar[] = {'A',      'B',      'C',      'D',      'E',      'F',      'G',      'H',      'I',      'J',      'K',      'L',      'M',      'N',      'O',      'P',      'Q',      'R',      'S',      'T',              'U',              'V',            'W',            'X',            'Y',            'Z'};
