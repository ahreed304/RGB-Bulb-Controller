#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8); // CE, CSN pins

const uint64_t pipeAddress[] = {0xF0F0F0F0AALL, 0xF0F0F0F066LL};
String dataIn;
int len;
bool isRepeatedCommand;

bool isFaster, isForward, isForwardColor;
float multiplier, multiplierFaster, multiplierSlower;
float delayTime, delayMin, delayMax;

int next, prev;
char color[] =  {"ABCDEFGHIJKL"};
char pattern[] =  {"0000.0000"};
