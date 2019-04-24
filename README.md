# Alexa Enabled Smart LED Clock (Wi-Fi)


This repository is to accompany my Alexa Enabled LED Clock Project video:

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/EQLDNrSjHa0/0.jpg)](https://www.youtube.com/watch?v=EQLDNrSjHa0)

## Alexa Emulation Library

This project was made to demonstrate the power of the ESPAlexa library made by AirCookie: https://github.com/Aircoookie/Espalexa

## Parts List
NodeMCU: https://amzn.to/2I89xDF

WS2812 LEDS 300/5m: https://amzn.to/2XEJPdR

5V Power Supply: https://amzn.to/2VlOns2

## 3D Printing

Check out the project on thingiverse for all the .stl files: https://www.thingiverse.com/thing:3241802

## Wiring Schematic

![alt text](https://github.com/thehookup/Alexa-Enabled-LED-Clock/blob/master/Schematic.jpg?raw=true)


## Recommended Tools

Ender3 3d Printer: https://amzn.to/2GcznnZ

## Alexa support using WiFiManager is built in.  Click on the "Releases" tab for a precompiled .bin file

## Usage
### Commands for this project are a little bit strange. Listed below are the controls:


### Device 1 (LED Light)
Brightness controls master brightness
Color controls color 1

### Device 2 (Clock Color 2)
Brightness controls effect
0-10 = Fill Solid (1 Color)
10-20 = 3 color chase
20-30 = 3 color random glitter
30-40 = Single Race (2 color)
40-50 = Double Crash (2 color)
50-60 = Rainbow 
60-70 = Fill Solid (3 Color)
70-80 = BPM (Color 1 Controlled)
80-90 = Twinkle (2 Color)
90-100 = Ripple (2 Color)

### Device 3 (Clock Color 3)
Brightness controls effect modifiers
Color controls color 3

### Device 4 (Clock Timer)
Brightess sets the timer ("Alexa set Clock Timer to 50" would give you a 50 minute timer)
Color sets daylight savings time.  If you set it to red it will turn on DST, blue will turn off DST.
