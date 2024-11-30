# ESP-IDF driver for LCD rewritten from Waveshare Arduino driver

## Overview
This Waveshare 2.4inch LCD module driver is just reworked 
[existing](https://www.waveshare.com/wiki/2.4inch_LCD_Module) driver for ESP-IDF
compatibility. Also basic buffer was add to address very slow byte by byte SPI
communication in ESP32 due to FreeRTOS overhead on each transaction.

## Pinout
Pinout can be changed in `DEV_Config.h` file and by default is following:

ESP pin 4 -> DC pin of LCD  
ESP pin 22 -> RST pin of LCD  
ESP pin 21 -> RST pin of LCD  
ESP pin 23 -> DIN pin of LCD  
ESP pin 18 -> CLK pin of LCD  
ESP pin 5 -> CS pin of LCD  

Those are the GPIO used in VSPI ESP interface, you can use HSPI by changing
pinout in the said file and function `setup_spi()` in `DEV_Config.c`(SPI3_HOST to SPI2_HOST).

## Usage
For driver usage you should take a look at the original guide, no external
interfaces were changed. From the `Underlying hardware interface` section only
`DEV_SPI_WRITE(unsigned char data)` function was changed to 
`DEV_SPI_WRITE_COMMAND(unsigned char data)`
and `DEV_SPI_WRITE_DATA(unsigned char data)` that reflect type of data to send.
Also it was a problem to port Chinese language support in newer compiler versions 
so it was excluded from project.

## License
The original driver was developed by Waveshare team under MIT license, all rights
for the software and hardware belong to them. This is a modification for ESP-IDF
development environment.

