//include RF24 libraries for NRF24L01 radio transceiver
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

//include library for serial monitor to receive commands from USB
#include <SPI.h>

RF24 radio(7, 8); // create RF24 object (CE, CSN pin numbers chosen on Arduino)

const uint64_t pipeAddress[] = {0xF0F0F0F0AALL, 0xF0F0F0F066LL}; //Addresses used for radio connections.  Only the first one is used as of now.  

const char defaultCommand[] =  "0000.0000"; //format of messages broadcast to receivers.  One '0' for every light bulb
const int defaultCommandLength = sizeof(defaultCommand);

const char color[] =  "ABCDEFGHIJKL";  //each letter represents a color that light bulbs can change to

asd;lkjasdf;lkjasd;lkaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa