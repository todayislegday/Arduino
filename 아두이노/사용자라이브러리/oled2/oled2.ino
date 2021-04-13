
/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using SPI to communicate
 4 or 5 pins are required to interface.

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   12
#define OLED_CLK   13
#define OLED_DC    4
#define OLED_CS    5
#define OLED_RESET 14
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Comment out above, uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16


 const unsigned char myBitmap1 [] PROGMEM = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x7f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xc3, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xfc, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 
  0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x30, 0x3f, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 
  0xff, 0xf0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x9f, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 
  0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xff, 
  0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 
  0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 
  0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 
  0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 
  0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 
  0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xf7, 0xff, 
  0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xfb, 0xff, 0x9f, 0xff, 0x9f, 0xe7, 0xfb, 0xff, 
  0xff, 0xe7, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xcf, 0xfb, 0xff, 0x8f, 0xff, 0x8f, 0xf7, 0xfb, 0xff, 
  0xff, 0xe7, 0xff, 0xe7, 0xff, 0xf1, 0xff, 0xcf, 0xfb, 0xff, 0x6f, 0xff, 0x8f, 0xc7, 0xfb, 0xff, 
  0xff, 0xf7, 0xff, 0xe7, 0xff, 0xf1, 0xff, 0xcf, 0xfb, 0xff, 0x6f, 0xff, 0x30, 0xef, 0xfb, 0xff, 
  0xff, 0xf7, 0xff, 0xc7, 0xff, 0xf4, 0x00, 0x1f, 0xf8, 0x00, 0x70, 0x00, 0x3f, 0xef, 0xfd, 0xff, 
  0xff, 0xf7, 0xff, 0xd3, 0xff, 0xe6, 0x1f, 0x3f, 0xfe, 0xff, 0xf3, 0xff, 0xff, 0xef, 0xfd, 0xff, 
  0xff, 0xf7, 0xff, 0x98, 0x00, 0x07, 0xff, 0xbf, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xfd, 0xff, 
  0xff, 0xf7, 0xff, 0x38, 0x1f, 0xff, 0xff, 0xbf, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xfd, 0xff, 
  0xff, 0xe0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xbf, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xfd, 0xff, 
  0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xfe, 0xff, 0xfd, 0xff, 0xff, 0xf7, 0xfd, 0xff, 
  0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xfe, 0xff, 0xfd, 0xdf, 0xff, 0xf7, 0xfd, 0xff, 
  0xff, 0xfd, 0xff, 0xfd, 0xfc, 0xff, 0xff, 0x9f, 0xfe, 0xff, 0xfd, 0xdf, 0xff, 0xf7, 0xfd, 0xff, 
  0xff, 0xfd, 0xff, 0xfd, 0xfc, 0xff, 0xff, 0x9f, 0xfe, 0xfb, 0xfd, 0xdf, 0xdf, 0xf7, 0xfd, 0xff, 
  0xff, 0xf9, 0xff, 0xff, 0xfc, 0xff, 0xff, 0x9f, 0xfe, 0xe0, 0x7f, 0x9f, 0x9f, 0xf7, 0xf9, 0xff, 
  0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xfe, 0xfc, 0xff, 0xff, 0x67, 0xf7, 0xfb, 0xff, 
  0xff, 0xf9, 0xf3, 0xff, 0xff, 0xf9, 0xff, 0x9f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xfb, 0xff, 
  0xff, 0xf9, 0xe2, 0x7f, 0xff, 0xf8, 0xbf, 0x9f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xf3, 0xff, 
  0xff, 0xf9, 0xc8, 0xff, 0xff, 0xf2, 0x7f, 0xbf, 0xfe, 0xff, 0xff, 0xef, 0xff, 0xf7, 0xf7, 0xff, 
  0xff, 0xfb, 0xd9, 0xe7, 0xff, 0x3e, 0xff, 0xbf, 0xfe, 0xff, 0xe7, 0xcf, 0xff, 0xf7, 0xe7, 0xff, 
  0xff, 0xfb, 0xff, 0xf7, 0xfe, 0x3f, 0xff, 0xbf, 0xfc, 0xff, 0xf3, 0xcf, 0xff, 0xf7, 0xef, 0xff, 
  0xff, 0xfb, 0xff, 0xf3, 0xfc, 0x7f, 0xff, 0xbf, 0xfd, 0xff, 0xf8, 0x3f, 0xff, 0xf7, 0xcf, 0xff, 
  0xff, 0xfb, 0xff, 0xf9, 0xf8, 0xff, 0xff, 0xbf, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xdf, 0xff, 
  0xff, 0xfb, 0xff, 0xfc, 0x01, 0xff, 0xff, 0xbf, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x9f, 0xff, 
  0xff, 0xfb, 0xff, 0xff, 0x07, 0xff, 0xff, 0xbf, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xcf, 0xbf, 0xff, 
  0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0x01, 0xc0, 0x00, 0xa0, 0xff, 0xbf, 0xff, 
  0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xbf, 0xff, 
  0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 
  0xff, 0xfc, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 
  0xff, 0xfe, 0x03, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 
  0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xef, 0xdf, 0xff, 0xff, 0xff, 0x7f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xe7, 0xcf, 0xff, 0xff, 0xff, 0x7f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xf7, 0xc7, 0x8f, 0xff, 0xff, 0xff, 0x7f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x7d, 0xf7, 0xd7, 0xb7, 0xff, 0xff, 0xff, 0x7f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xfd, 0xf7, 0xdb, 0x37, 0xff, 0xff, 0xff, 0x3f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfc, 0x07, 0x98, 0x7b, 0xff, 0xff, 0xff, 0xbf, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfc, 0x77, 0x9c, 0xf9, 0xff, 0xff, 0xff, 0xbf, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfd, 0xf7, 0xbf, 0xfd, 0xff, 0xff, 0xff, 0xdf, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xfd, 0xf7, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbd, 0xfd, 0xf7, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x99, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff
 };
const unsigned char sunny64 [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 
  0xff, 0xe3, 0xff, 0xfc, 0x3f, 0xff, 0xc7, 0xff, 0xff, 0xc1, 0xff, 0xfc, 0x7f, 0xff, 0x83, 0xff, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xfe, 0x07, 0xff, 
  0xff, 0xe0, 0x3f, 0xe0, 0x07, 0xfc, 0x07, 0xff, 0xff, 0xf0, 0x3f, 0x00, 0x00, 0xfc, 0x0f, 0xff, 
  0xff, 0xf8, 0x1c, 0x00, 0x00, 0x78, 0x1f, 0xff, 0xff, 0xfc, 0x38, 0x00, 0x00, 0x1c, 0x3f, 0xff, 
  0xff, 0xff, 0x70, 0x07, 0xe0, 0x0e, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0xfc, 0x07, 0xff, 0xff, 
  0xff, 0xff, 0xc0, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0x81, 0xff, 0xff, 
  0xff, 0xff, 0x03, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xe0, 0xff, 0xff, 
  0xff, 0xfe, 0x0f, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xf0, 0x7f, 0xff, 
  0xff, 0xfe, 0x1f, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 
  0xff, 0xfc, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 
  0xc0, 0x0c, 0x3f, 0xff, 0xff, 0xfc, 0x30, 0x03, 0xc0, 0x0c, 0x3f, 0xff, 0xff, 0xfc, 0x30, 0x03, 
  0xc0, 0x0c, 0x3f, 0xff, 0xff, 0xfc, 0x30, 0x03, 0xc0, 0x1c, 0x3f, 0xff, 0xff, 0xfc, 0x30, 0x07, 
  0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 
  0xff, 0xfc, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xf8, 0x7f, 0xff, 
  0xff, 0xfe, 0x0f, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xf0, 0x7f, 0xff, 
  0xff, 0xff, 0x07, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xc1, 0xff, 0xff, 
  0xff, 0xff, 0x81, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0x03, 0xff, 0xff, 
  0xff, 0xff, 0xe0, 0x3f, 0xfc, 0x07, 0xff, 0xff, 0xff, 0xff, 0x70, 0x07, 0xe0, 0x0e, 0xff, 0xff, 
  0xff, 0xfc, 0x38, 0x00, 0x00, 0x1c, 0x3f, 0xff, 0xff, 0xf8, 0x1e, 0x00, 0x00, 0x78, 0x1f, 0xff, 
  0xff, 0xf0, 0x3f, 0x00, 0x00, 0xfc, 0x0f, 0xff, 0xff, 0xe0, 0x3f, 0xe0, 0x07, 0xfc, 0x07, 0xff, 
  0xff, 0xc0, 0x7f, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 
  0xff, 0xc1, 0xff, 0xfc, 0x3f, 0xff, 0x83, 0xff, 0xff, 0xe7, 0xff, 0xfc, 0x3f, 0xff, 0xe7, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
// '3741357-cloud-cloudy-partly-cloudy64-weather_108867', 64x64px
const unsigned char cloudy64[] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xfe, 0xff, 0xe7, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 
  0xfc, 0x1f, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 
  0xff, 0x0f, 0x80, 0xf0, 0xfc, 0x00, 0xff, 0xff, 0xff, 0x9e, 0x00, 0x33, 0xe0, 0x00, 0x1f, 0xff, 
  0xff, 0xfc, 0x00, 0x1f, 0x80, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x3e, 0x0f, 0x01, 0xfe, 0x03, 0xff, 
  0xff, 0xf8, 0x7f, 0x86, 0x0f, 0xff, 0xc1, 0xff, 0xff, 0xf0, 0xff, 0xc0, 0x3f, 0xff, 0xe0, 0xff, 
  0xff, 0xf1, 0xff, 0xc0, 0x7f, 0xff, 0xf8, 0x7f, 0xff, 0xf1, 0xf0, 0x40, 0xff, 0xff, 0xfc, 0x3f, 
  0xff, 0xf1, 0x80, 0x01, 0xff, 0xff, 0xfe, 0x3f, 0xfc, 0x70, 0x00, 0x03, 0xff, 0xff, 0xfe, 0x1f, 
  0xe0, 0x30, 0x07, 0x83, 0xff, 0xff, 0xff, 0x0f, 0xe0, 0x70, 0x3f, 0xc7, 0xff, 0xff, 0xff, 0x8f, 
  0xe3, 0xe0, 0xff, 0x87, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xe1, 0xff, 0x8f, 0xff, 0xff, 0xff, 0x87, 
  0xff, 0xc3, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x87, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xc7, 
  0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 
  0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 
  0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 
  0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 
  0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 
  0xff, 0x8f, 0xff, 0xf3, 0xff, 0xff, 0xff, 0x1f, 0xff, 0x87, 0xff, 0xe1, 0xff, 0xff, 0xfe, 0x1f, 
  0xff, 0xc7, 0xff, 0xf0, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xc3, 0xff, 0xf0, 0x7f, 0xff, 0xf8, 0x7f, 
  0xff, 0xe1, 0xff, 0xf8, 0x3f, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0xff, 0xf8, 0x0f, 0xff, 0xc1, 0xff, 
  0xff, 0xf8, 0x3f, 0xe0, 0x03, 0xff, 0x03, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x80, 0x00, 0x07, 0xff, 
  0xff, 0xfe, 0x00, 0x03, 0xc0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x80, 0x0f, 0xf8, 0x00, 0x7f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
// '3741359-cloud-overcast-weather_108879', 64x64px
const unsigned char overcast64 [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x3f, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 
  0xff, 0xff, 0xfc, 0x00, 0x60, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xfe, 0x01, 0xff, 0xff, 
  0xff, 0xfc, 0x00, 0x1f, 0xff, 0x81, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x3f, 0xf0, 0x00, 0xff, 0xff, 
  0xff, 0xe0, 0x00, 0x7f, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xc0, 0x00, 0x3e, 0x00, 0x00, 0x3f, 0xff, 
  0xff, 0x80, 0x60, 0x1c, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x81, 0xf8, 0x10, 0x00, 0x00, 0x07, 0xff, 
  0xff, 0x03, 0xfc, 0x00, 0x0f, 0xfc, 0x03, 0xff, 0xff, 0x07, 0xfe, 0x00, 0x3f, 0xff, 0x01, 0xff, 
  0xff, 0x07, 0xe2, 0x00, 0xff, 0xff, 0x80, 0xff, 0xff, 0x0e, 0x00, 0x01, 0xff, 0xff, 0xe0, 0x7f, 
  0xff, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 0x3f, 
  0xff, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0x00, 0x3e, 0x0f, 0xff, 0xff, 0xfc, 0x1f, 
  0xff, 0x01, 0xfc, 0x0f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0x03, 0xfc, 0x1f, 0xff, 0xff, 0xfc, 0x1f, 
  0xfe, 0x07, 0xfc, 0x1f, 0xff, 0xff, 0xfe, 0x0f, 0xfe, 0x0f, 0xfc, 0x1f, 0xff, 0xff, 0xfe, 0x0f, 
  0xfc, 0x1f, 0xfe, 0x3f, 0xff, 0xff, 0xfe, 0x0f, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 
  0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 
  0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 
  0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 
  0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xfc, 0x1f, 0xff, 0xcf, 0xff, 0xff, 0xf8, 0x3f, 
  0xfc, 0x1f, 0xff, 0x87, 0xff, 0xff, 0xf8, 0x3f, 0xfc, 0x0f, 0xff, 0x83, 0xff, 0xff, 0xf0, 0x3f, 
  0xfe, 0x0f, 0xff, 0x81, 0xff, 0xff, 0xe0, 0x7f, 0xfe, 0x07, 0xff, 0x80, 0xff, 0xff, 0xc0, 0xff, 
  0xff, 0x03, 0xff, 0xc0, 0x7f, 0xff, 0x01, 0xff, 0xff, 0x80, 0xff, 0x80, 0x1f, 0xfc, 0x03, 0xff, 
  0xff, 0xc0, 0x08, 0x00, 0x00, 0x80, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
  0xff, 0xf0, 0x00, 0x06, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x0f, 0x80, 0x00, 0x7f, 0xff, 
  0xff, 0xff, 0x00, 0x3f, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
// 'rain_weather64_3371', 64x64px
const unsigned char rainy64 [] PROGMEM = {
  0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf7, 
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xe3, 
  0xf9, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xc1, 0xf8, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0x81, 
  0xf0, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0x80, 0xe0, 0x7f, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0x80, 
  0xe0, 0x7f, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0xe0, 0x3f, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0x00, 
  0xc0, 0x3f, 0xc0, 0x00, 0x00, 0x03, 0xff, 0x80, 0xc0, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xc1, 
  0xc0, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe7, 0xe0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
  0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 
  0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
  0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
  0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
  0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x03, 0xff, 0x00, 0x18, 0x18, 0x00, 0xff, 0xc0, 
  0x0f, 0xff, 0xc0, 0x78, 0x1e, 0x03, 0xff, 0xf0, 0x1f, 0xff, 0xf0, 0xf8, 0x1f, 0x0f, 0xff, 0xf8, 
  0x7f, 0xff, 0xf9, 0xf8, 0x1f, 0x9f, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xfe, 0x1f, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xfc, 0x0f, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xfe, 0x07, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xf0, 0x3f, 0xff, 0xff, 0xff, 
  0xff, 0xfe, 0x01, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x80, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xff, 0xff
};

// 'sleet_application_climate64_2877', 64x64px
const unsigned char sleet64 [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x03, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 
  0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0x00, 0x1f, 0xff, 
  0xff, 0xff, 0xff, 0x80, 0x7f, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xf8, 0x0f, 0xff, 
  0xff, 0xff, 0x80, 0x03, 0xff, 0xfc, 0x07, 0xff, 0xff, 0xff, 0x00, 0x03, 0xff, 0xfe, 0x07, 0xff, 
  0xff, 0xfc, 0x00, 0x07, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x0f, 0xff, 0xff, 0x03, 0xff, 
  0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0x03, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0x80, 0x7f, 
  0xff, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0x80, 0x3f, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x0f, 
  0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x80, 0x07, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x07, 
  0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x03, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 
  0xe0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 
  0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x01, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x03, 
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
  0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 
  0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0x00, 0x7f, 
  0xff, 0x81, 0xff, 0xfd, 0xff, 0xfe, 0x00, 0x7f, 0xfe, 0x01, 0xff, 0xf8, 0xff, 0xfe, 0x00, 0x7f, 
  0xfc, 0x01, 0xff, 0xf8, 0xff, 0xfe, 0x00, 0x7f, 0xf8, 0x01, 0xff, 0x18, 0xc7, 0xfc, 0x00, 0x7f, 
  0xf8, 0x01, 0xff, 0x08, 0x87, 0xfe, 0x00, 0xff, 0xf8, 0x01, 0xff, 0x80, 0x07, 0xfe, 0x00, 0xff, 
  0xf8, 0x01, 0xff, 0xc0, 0x0f, 0xff, 0x01, 0xff, 0xf8, 0x03, 0xff, 0xe0, 0x1f, 0xff, 0x83, 0xff, 
  0xf8, 0x03, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 
  0xff, 0x1f, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x87, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x08, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x18, 0xe7, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff
};

// '3741358-christmas-cold-snow64-weather_108876', 64x64px
const unsigned char snow64 [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x38, 0x1c, 0x7f, 0xff, 0xff, 
  0xff, 0xff, 0xfc, 0x18, 0x18, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x08, 0x10, 0x3f, 0xff, 0xff, 
  0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0x80, 0x01, 0xff, 0x8f, 0xff, 
  0xff, 0xe0, 0xff, 0xc0, 0x03, 0xff, 0x07, 0xff, 0xff, 0xe0, 0x7f, 0xf0, 0x0f, 0xfe, 0x07, 0xff, 
  0xff, 0xe0, 0x3f, 0xf8, 0x1f, 0xfc, 0x07, 0xff, 0xff, 0xf0, 0x1f, 0xf8, 0x1f, 0xf8, 0x0f, 0xff, 
  0xff, 0xf8, 0x0f, 0xf8, 0x1f, 0xf0, 0x1f, 0xff, 0xff, 0xfc, 0x07, 0xf8, 0x1f, 0xe0, 0x3f, 0xff, 
  0xff, 0xfe, 0x03, 0xf8, 0x1f, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0x01, 0xf8, 0x1f, 0x80, 0xff, 0xff, 
  0xff, 0xff, 0x80, 0xf8, 0x1f, 0x01, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x78, 0x1e, 0x03, 0xff, 0xff, 
  0xfc, 0x7f, 0xe0, 0x38, 0x1c, 0x07, 0xfe, 0x3f, 0xf8, 0x3f, 0xf0, 0x18, 0x18, 0x0f, 0xfc, 0x1f, 
  0xf8, 0x1f, 0xf8, 0x08, 0x10, 0x1f, 0xf8, 0x1f, 0xf8, 0x0f, 0xfc, 0x00, 0x00, 0x3f, 0xf0, 0x1f, 
  0xfc, 0x07, 0xfe, 0x00, 0x00, 0x7f, 0xe0, 0x3f, 0xfe, 0x07, 0xff, 0x00, 0x00, 0xff, 0xe0, 0x7f, 
  0xff, 0x03, 0xff, 0x80, 0x01, 0xff, 0xc0, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
  0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 
  0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x03, 0xff, 0x80, 0x01, 0xff, 0xc0, 0xff, 
  0xfe, 0x07, 0xff, 0x00, 0x00, 0xff, 0xe0, 0x7f, 0xfc, 0x07, 0xfe, 0x00, 0x00, 0x7f, 0xe0, 0x3f, 
  0xf8, 0x0f, 0xfc, 0x00, 0x00, 0x3f, 0xf0, 0x1f, 0xf8, 0x1f, 0xf8, 0x08, 0x10, 0x1f, 0xf8, 0x1f, 
  0xf8, 0x3f, 0xf0, 0x18, 0x18, 0x0f, 0xfc, 0x1f, 0xfc, 0x7f, 0xe0, 0x38, 0x1c, 0x07, 0xfe, 0x3f, 
  0xff, 0xff, 0xc0, 0x78, 0x1e, 0x03, 0xff, 0xff, 0xff, 0xff, 0x80, 0xf8, 0x1f, 0x01, 0xff, 0xff, 
  0xff, 0xff, 0x01, 0xf8, 0x1f, 0x80, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xf8, 0x1f, 0xc0, 0x7f, 0xff, 
  0xff, 0xfc, 0x07, 0xf8, 0x1f, 0xe0, 0x3f, 0xff, 0xff, 0xf8, 0x0f, 0xf8, 0x1f, 0xf0, 0x1f, 0xff, 
  0xff, 0xf0, 0x1f, 0xf8, 0x1f, 0xf8, 0x0f, 0xff, 0xff, 0xe0, 0x3f, 0xf8, 0x1f, 0xfc, 0x07, 0xff, 
  0xff, 0xe0, 0x7f, 0xf0, 0x0f, 0xfe, 0x07, 0xff, 0xff, 0xe0, 0xff, 0xc0, 0x03, 0xff, 0x07, 0xff, 
  0xff, 0xf1, 0xff, 0x80, 0x01, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 
  0xff, 0xff, 0xfc, 0x08, 0x10, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x18, 0x18, 0x3f, 0xff, 0xff, 
  0xff, 0xff, 0xfe, 0x38, 0x1c, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
// 'sunandcloudwithrain64_87433', 64x64px
const unsigned char rcd64 [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xfe, 0x1f, 0xfc, 0x7f, 
  0xff, 0xff, 0xff, 0x87, 0xff, 0x3f, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xf0, 0x7f, 
  0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xe0, 0xff, 
  0xff, 0xff, 0xff, 0xf1, 0xfc, 0x0f, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xf0, 0x03, 0xf7, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x7f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x1f, 0xe7, 0xf8, 0x1f, 0xff, 
  0xff, 0xff, 0x00, 0x07, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xfc, 0x00, 0x03, 0xff, 0xfe, 0x1f, 0xff, 
  0xff, 0xf8, 0x00, 0x01, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0xff, 0xff, 0x0f, 0x01, 
  0xff, 0xe0, 0x1f, 0xc0, 0x7f, 0xff, 0x0f, 0x00, 0xff, 0xe0, 0x7f, 0xe0, 0x3f, 0xff, 0x0e, 0x00, 
  0xff, 0xc0, 0xff, 0xf0, 0x3f, 0xff, 0x0f, 0x01, 0xff, 0xc1, 0xff, 0xf8, 0x3f, 0xff, 0x0f, 0xff, 
  0xff, 0xc1, 0xff, 0xfc, 0x1f, 0xfe, 0x0f, 0xff, 0xff, 0x81, 0xff, 0xfc, 0x03, 0xfe, 0x1f, 0xff, 
  0xfc, 0x03, 0xff, 0xfc, 0x00, 0x7e, 0x1f, 0xff, 0xf8, 0x03, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xff, 
  0xe0, 0x03, 0xff, 0xfe, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xfe, 0x00, 0x07, 0xff, 0xff, 
  0xc0, 0x3f, 0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0x03, 0xe3, 0xff, 
  0x81, 0xff, 0xff, 0xff, 0xff, 0x81, 0xe1, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xe0, 0xff, 
  0x07, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xf0, 0x7f, 0x07, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xf8, 0x3f, 
  0x07, 0xfe, 0x7f, 0xfe, 0x7f, 0xc1, 0xfc, 0x7f, 0x07, 0xfc, 0x3f, 0xfc, 0x3f, 0xc1, 0xfe, 0xff, 
  0x03, 0xf8, 0x3f, 0xfc, 0x1f, 0xc1, 0xff, 0xff, 0x83, 0xf8, 0x3f, 0xf8, 0x1f, 0xc1, 0xff, 0xff, 
  0x81, 0xf8, 0x3f, 0xf8, 0x3f, 0x81, 0xff, 0xff, 0xc0, 0xf0, 0x7f, 0xf8, 0x3e, 0x03, 0xff, 0xff, 
  0xc0, 0x70, 0x78, 0xf8, 0x38, 0x07, 0xff, 0xff, 0xe0, 0x78, 0x70, 0x7c, 0x70, 0x07, 0xff, 0xff, 
  0xf0, 0xff, 0xf0, 0x7f, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xf0, 0x3f, 0xff, 0xff, 
  0xff, 0xff, 0xe0, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xe3, 0xe0, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xf1, 0xe0, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xc1, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0x83, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0xef, 0xc1, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xc3, 0x87, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0x83, 0xf7, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  int a=-3;
 display.clearDisplay();
 display.setTextColor(WHITE);
display.setCursor(50,24);
display.print(a);
display.display();
  delay(2000);
  
}
void loop(){
  
  }
  
