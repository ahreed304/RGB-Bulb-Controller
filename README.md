# RGB-Bulb-Controller

This project allows you to use Amazon Alexa to voice-control any device that uses a standard IR remote control.  It is based on a controller I wrote for Yangcsl brand RGB light bulbs. This RGB controller serves as a viable alternative to the expensive Phillips Hue brand RGB bulbs at a fraction of the price.  Instead of WiFi modules, this project relies on cheaper RF transceivers that operate in the 2.4 GHz unlicensed band.  This allows any number of devices to be controlled within a possible area of 2 kilometers or more.

## Requirements

- Rasberry Pi with Node-Red installed

- Arduinos (Nano, Uno, or other)

- NRF24L01 Radio Transceivers

- IR LEDs

- Yangcsl RGB Light bulbs or any other device using an IR remote control such as a TV, cable box, or stereo.


## Description

1) Raspberry Pi running Node-Red is emulating many smart-bulbs and/or other devices.

2) Voice command is spoken to Alexa ("Alexa, Kitchen lights on";  "Alexa, all lights green";  "Alexa, TV volume up").

3) Alexa sends data associated with command to specified Node-Red emulator node.  

4) Node-Red executes javascricpt code that interprets Alexa's data. The command is translated to standardized format.

5) Formatted command is outputted to an Arduino via USB serial port.

6) Arduino interprets command and broadcasts it via a connected NRF24L01 radio transceiver.

7) Many other Arduinos receive the broadcast via a connected NRF24L01 radio transceiver.

8) Receiver-Arduinos interpret the commands and output IR signals to RGB light bulbs or other devices via a connected IR LED.

9) Command reaches final destination (RGB bulb or other device).  Repeat.

## Created by

Austin Reed

2018
