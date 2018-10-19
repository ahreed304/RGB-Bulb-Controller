#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8); // CE, CSN 

const uint64_t pipeAddress[] = {0xF0F0F0F0AALL, 0xF0F0F0F066LL};
String dataIn;
int len;

bool isForwards;
float multiplier, multiplierForwards, multiplierBackwards;
float delayTime, delayMin, delayMax;

int next;
char color[12] =  {'B', 'C', 'D', 'E',
                   'F', 'G', 'H', 'I',
                   'J', 'K', 'L'};
char pattern[10] =  {'0', '0', '0', '0', '.', 
                     '0', '0', '0', '0'};
