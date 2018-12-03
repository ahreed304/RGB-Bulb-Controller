# RGB-Bulb-Controller

## Version 2.0.01

This project allows you to use Amazon Alexa to voice-control any device that uses a standard IR remote control.  It is based on a controller I wrote for Yangcsl brand RGB light bulbs. This RGB controller serves as a viable alternative to the expensive Phillips Hue brand RGB bulbs at a fraction of the price.  Instead of WiFi modules, this project relies on cheaper RF transceivers that operate in the 2.4 GHz unlicensed band.  This allows any number of devices to be controlled within a possible area of 2 kilometers or more.

## Requirements

- Raspberry Pi with Node-Red installed

- Arduinos (Nano, Uno, or other)

- NRF24L01 Radio Transceivers

- IR LEDs

- Yangcsl RGB Light bulbs or any other device using an IR remote control such as a TV, cable box, or stereo.


## Description
This project arose out of a desire to have better control over the eight Yangscl RGB bulbs throughout my house. Each bulb came with a small IR remote control with very short range.  The remotes control the color, brightness, on/off state, and other settings for each bulb.  I used an Arduino and an IR receiver module to learn the IR code associated with each command.  I then wrote a program in C++ for an Arduiuno Nano with an attached IR LED to transmit these commands and control the light bulb.  Commands are received from an attached NRF24L01 radio transceiver module.  There are nine of these units total: one for each RGB light, and a special version that controls my TV and stereo.  (see photos in "Reference" section)

Node-Red, a powerful IOT software tool for the Raspberry Pi, has the ability to emulate smart devices on a LAN.  In this example, I have emulated several smart lights so that Node-Red can receive voice commands from Amazon Alexa.  It then processes these commands and passes them to an Arduino which then broadcasts the commands through an NRF24L01 radio transceiver (see photos in "Reference" section).  The nine reciever Arduinos receive the commands and pass them to the RGB bulbs, TV, and stereo accordingly.  

The whole process takes a fraction of a second and is very reliable.  The commands are formatted in such a way that I can send a different command to each device at the same time.  This makes it easy to control light bulbs in groups.  It also makes it possible to design complex, rhythmic, colorful lighting patterns.  I have been using different versions of this code to control the lights in my house for several months, and it works very well.  

## Future Releases

- more colorful lighting patterns and modes

- Smart switch control (RF433)

- code refactoring / general improvements

- New node on Node-Red

- sync lights to music

## Created by

Austin Reed, 
2018
