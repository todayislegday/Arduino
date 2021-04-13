#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <time.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


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

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16  

const char* ssid = "U+Net16C5";
const char* password = "1C18047287";

int nt=0; //현재기온
int tmn=0; //최저기온
int tmx=0; //최고기온
int sky[4]={0,0,0,0}; //하늘상태
int pty=0; //강수량 상태
int wloop=0; 
int wloopi=0; 

int timezone = 9;

int c_result=0;



const unsigned char boot [] PROGMEM = {
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
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 
  0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 
  0x00, 0x0f, 0x80, 0x01, 0x80, 0x01, 0xf0, 0x00, 0x00, 0x07, 0xc0, 0x3f, 0xfc, 0x03, 0xe0, 0x00, 
  0x00, 0x03, 0xc0, 0xff, 0xff, 0x03, 0xc0, 0x00, 0x00, 0x01, 0xc3, 0xff, 0xff, 0xc3, 0x80, 0x00, 
  0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x01, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x1e, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00, 
  0x00, 0x00, 0x78, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x0e, 0x00, 0x00, 
  0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x07, 0x00, 0x00, 
  0x00, 0x01, 0xe0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 
  0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 
  0x0f, 0xc1, 0xc0, 0x00, 0x00, 0x03, 0x83, 0xf0, 0x1f, 0xe3, 0xc0, 0x00, 0x00, 0x03, 0xc7, 0xf8, 
  0x1f, 0xe3, 0xc0, 0x00, 0x00, 0x03, 0xc7, 0xf8, 0x0f, 0xc1, 0xc0, 0x00, 0x00, 0x03, 0x83, 0xf0, 
  0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 
  0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x07, 0x80, 0x00, 
  0x00, 0x00, 0xe0, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 
  0x00, 0x00, 0x70, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x1e, 0x00, 0x00, 
  0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x78, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0x80, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 
  0x00, 0x01, 0xc3, 0xff, 0xff, 0xc3, 0x80, 0x00, 0x00, 0x03, 0xc0, 0xff, 0xff, 0x03, 0xc0, 0x00, 
  0x00, 0x07, 0xc0, 0x3f, 0xfc, 0x03, 0xe0, 0x00, 0x00, 0x0f, 0x80, 0x01, 0x80, 0x01, 0xf0, 0x00, 
  0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 
  0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char c [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0xc0, 0x7f, 0x80, 0x02, 0x61, 0xff, 0x80, 0x02, 0x23, 0xfb, 0x80, 0x03, 0x47, 0xc0, 0x00, 
  0x01, 0x87, 0x80, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 
  0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 
  0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x03, 0xff, 0x80, 0x00, 0x01, 0xff, 0x80, 
  0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
 
const unsigned char sunny [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 
  0x00, 0x01, 0x80, 0x00, 0x06, 0x01, 0x80, 0x60, 0x07, 0x00, 0x00, 0xe0, 0x03, 0x87, 0xe1, 0xc0, 
  0x01, 0x9f, 0xf9, 0x80, 0x00, 0x3c, 0x3c, 0x00, 0x00, 0x70, 0x0e, 0x00, 0x00, 0xe0, 0x07, 0x00, 
  0x00, 0xc0, 0x03, 0x00, 0x01, 0xc0, 0x03, 0x80, 0x01, 0x80, 0x01, 0x80, 0x7d, 0x80, 0x01, 0xbe, 
  0x7d, 0x80, 0x01, 0xbe, 0x01, 0x80, 0x01, 0x80, 0x01, 0xc0, 0x03, 0x80, 0x00, 0xc0, 0x03, 0x00, 
  0x00, 0xe0, 0x07, 0x00, 0x00, 0x70, 0x0e, 0x00, 0x00, 0x3c, 0x3c, 0x00, 0x01, 0x9f, 0xf9, 0x80, 
  0x03, 0x87, 0xe1, 0xc0, 0x07, 0x00, 0x00, 0xe0, 0x06, 0x01, 0x80, 0x60, 0x00, 0x01, 0x80, 0x00, 
  0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char rain [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x03, 0xc1, 0xe0, 
  0x00, 0x07, 0x00, 0x70, 0x01, 0xfe, 0x00, 0x30, 0x07, 0xfc, 0x00, 0x18, 0x0e, 0x18, 0x00, 0x18, 
  0x1c, 0x18, 0x00, 0x1c, 0x18, 0x10, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x0c, 
  0x30, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x18, 0x30, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x00, 0x38, 
  0x1c, 0x0e, 0x00, 0x70, 0x0e, 0x0f, 0x81, 0xe0, 0x07, 0xff, 0xff, 0xc0, 0x03, 0xf8, 0xff, 0x00, 
  0x03, 0x01, 0x00, 0x00, 0x03, 0x31, 0x98, 0x00, 0x06, 0x33, 0x18, 0x00, 0x06, 0x63, 0x30, 0x00, 
  0x00, 0x60, 0x30, 0x00, 0x0c, 0x06, 0x00, 0x00, 0x1c, 0xce, 0x60, 0x00, 0x19, 0xcc, 0xe0, 0x00, 
  0x01, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
 const unsigned char windy [] PROGMEM = {
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x1f, 0xe0, 0x00, 
  0x00, 0x38, 0x70, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x60, 0x1b, 0xc0, 0x00, 0x60, 0x1b, 0xf0, 
  0x00, 0x60, 0x18, 0x38, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x70, 0x0c, 
  0x0f, 0xff, 0xe0, 0x0c, 0x0f, 0xff, 0x80, 0x0c, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x38, 
  0x3f, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xff, 0xfc, 0x00, 0x07, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0xc3, 0x00, 
  0x00, 0x00, 0xc3, 0x00, 0x00, 0x00, 0xe7, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3c, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char heart [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xc0, 0x7c, 0x00, 0x1f, 0xf1, 0xff, 0x00, 0x38, 0x7b, 0xc3, 0x80, 0x70, 0x1f, 0x01, 0xc0, 
  0x60, 0x0e, 0x00, 0xc0, 0xc0, 0x04, 0x00, 0x60, 0xc0, 0x00, 0x00, 0x60, 0xc0, 0x00, 0x30, 0x60, 
  0xc0, 0x00, 0xfc, 0x60, 0x60, 0x01, 0xfe, 0xe0, 0x60, 0x03, 0xff, 0xf8, 0x70, 0x03, 0xff, 0xfc, 
  0x30, 0x03, 0xff, 0xfe, 0x18, 0x03, 0xff, 0xff, 0x0c, 0x03, 0xff, 0xff, 0x07, 0x01, 0xff, 0xff, 
  0x03, 0x81, 0xff, 0xfe, 0x01, 0xc0, 0xff, 0xfe, 0x00, 0xe0, 0xff, 0xfc, 0x00, 0x71, 0xff, 0xf8, 
  0x00, 0x3f, 0xff, 0xf0, 0x00, 0x1f, 0x3f, 0x80, 0x00, 0x0e, 0x3e, 0x00, 0x00, 0x00, 0x18, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int counting=1;

void setup() {

  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
 display.clearDisplay();
 display.setTextColor(WHITE);
 display.setTextSize(2);
display.drawBitmap(0, 0, boot, 128, 64, WHITE);
display.display();
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  Serial.println("\nConnecting to WiFi");
  delay(10000);
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect(true);
    Serial.println("can't connect to WiFi");
    display.clearDisplay();
    display.setCursor(10,27);
    display.println("can't connect to AP");
    display.display();
    smartconfig();
  }
  display.setCursor(0,27);
  display.clearDisplay();
    display.println("connected!");
    display.display();
    delay(1000);
  display.clearDisplay();
 
  configTime(timezone * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.println("\nWaiting for time");

  while (!time(NULL)) {

    Serial.print(".");

    delay(1000);

  }
  Serial.println("");
  
  while(counting){
    display.clearDisplay();
    display.setCursor(40,25);
   time_t now = time(NULL);
  struct tm* timeinfo;
  timeinfo=localtime(&now);
 countgettogether(timeinfo->tm_year,timeinfo->tm_mon,timeinfo->tm_mday);
 Serial.printf("%d일 사겼습니다.1\n", c_result);
 display.drawBitmap(0,16, heart, 32, 32, WHITE);
 display.drawBitmap(96,16, heart, 32, 32, WHITE);
  display.print(c_result);
  if(c_result>1000)
    counting=0;
delay(1000);
  }
   display.display();
   getwheatherinfo(2);
}
void loop() {
//  getwheatherinfo();
  time_t now = time(NULL);
  struct tm* timeinfo;
  timeinfo=localtime(&now);
  display.clearDisplay();
  drawweather();
  display.clearDisplay();
   if((timeinfo->tm_hour==0)&&(timeinfo->tm_min==0)&&(timeinfo->tm_sec==0||timeinfo->tm_sec==10)){
     countgettogether(timeinfo->tm_year,timeinfo->tm_mon,timeinfo->tm_mday);
     Serial.printf("사귄날짜 리셋\n");
   }
   if(((timeinfo->tm_hour==2&&timeinfo->tm_min==20)||(timeinfo->tm_hour==5&&timeinfo->tm_min==20)||(timeinfo->tm_hour==8&&timeinfo->tm_min==20)||(timeinfo->tm_hour==11&&timeinfo->tm_min==20)||(timeinfo->tm_hour==14&&timeinfo->tm_min==20)||(timeinfo->tm_hour==17&&timeinfo->tm_min==20)||(timeinfo->tm_hour==20&&timeinfo->tm_min==20)||(timeinfo->tm_hour==23&&timeinfo->tm_min==20))&&wloop==0){
         getwheatherinfo(timeinfo->tm_hour);  //한번 갱신하고 다시 실행 안되도록...
         wloop=1;
   }
   for(int i=0;i<5;i++){
   drawgettogetherday();
   drawtime();
   display.clearDisplay();
   }
      if(wloop!=0)
       wloopi++;
      if(wloopi==20)
       wloop=0;
       Serial.printf("%d %d\n",wloop,wloopi);
   }

void smartconfig(){ //기존 공유기 연결 못할시..
   WiFi.beginSmartConfig();
   Serial.println("Waiting for SmartConfig.");

  while (!WiFi.smartConfigDone()) {

  delay(500);
  Serial.print(".");
  Serial.println("");
  Serial.println("SmartConfig received.");

  //Wait for WiFi to connect to AP
  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected.");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  }
  }

void getwheatherinfo(int hour){//날씨 정보를 획득합니다.
    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://apis.data.go.kr/1360000/VilageFcstInfoService/getVilageFcst?serviceKey=7503qUB6FNb%2BuC5jrw1iycVdkNUroYZogV7Nav12eN5SdqjGsXoGzWv1OSJn4D7FTFHDfGgWas%2FQVJbUF9T30g%3D%3D&numOfRows=50&&base_date=20200424&base_time=0200&nx=57&ny=121&dataType=JSON")) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
         const size_t capacity=payload.length()*2;
          DynamicJsonDocument doc(capacity);

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  // Extract values
  Serial.println(F("Response:"));
  Serial.println(doc["response"]["body"]["numOfRows"].as<long>());

for(int i=0;i<doc["response"]["body"]["numOfRows"].as<long>();i++){
     if(strcmp("T3H",doc["response"]["body"]["items"]["item"][i]["category"].as<char *>())==0){
     nt=doc["response"]["body"]["items"]["item"][i]["fcstValue"].as<int>();
     break;
  }
    } 
  
  if(hour==2){//최저기온+최고기온 갱신
    for(int i=0;i<doc["response"]["body"]["numOfRows"].as<long>();i++){
     if(strcmp("TMN",doc["response"]["body"]["items"]["item"][i]["category"].as<char *>())==0){
     tmn=doc["response"]["body"]["items"]["item"][i]["fcstValue"].as<double>()*10/10;
  }
   if(strcmp("TMX",doc["response"]["body"]["items"]["item"][i]["category"].as<char *>())==0){
     tmx=doc["response"]["body"]["items"]["item"][i]["fcstValue"].as<double>()*10/10;
     break;
  }
    } 
    }
  if(hour==5||hour==8||hour==11){//최고기온 갱신
    for(int i=0;i<doc["response"]["body"]["numOfRows"].as<long>();i++){
    if(strcmp("TMX",doc["response"]["body"]["items"]["item"][i]["category"].as<char *>())==0){
     tmx=doc["response"]["body"]["items"]["item"][i]["fcstValue"].as<double>()*10/10;
     break;
  }
    } 
  }
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }

  }
void drawweather(){
  display.drawBitmap(0,0,sunny64,64,64, WHITE);
  display.drawBitmap(96,10,c,32,32, WHITE);
  display.setCursor(70,10);
   display.setTextSize(3);
  display.print(nt);
  display.setCursor(70,40);
  display.setTextSize(2);
  display.print(tmn);
  display.print("/");
  display.print(tmx);
  display.display();
  delay(5000);
  }  
void drawgettogetherday(){
   display.setCursor(40,25);
   display.setTextSize(2);
   time_t now = time(NULL);
  struct tm* timeinfo;
  timeinfo=localtime(&now);
  display.print(c_result);
 Serial.printf("%d일 사겼습니다.2\n", c_result);
  display.drawBitmap(0,16, heart, 32, 32, WHITE);
 display.drawBitmap(96,16, heart, 32, 32, WHITE);
 
  }
  
void drawtime(){
   display.setCursor(42,50);
    display.setTextSize(1);
   time_t now = time(NULL);
  struct tm* timeinfo;
  timeinfo=localtime(&now);
   if(timeinfo->tm_hour<10)
  display.print(0);
  display.print(timeinfo->tm_hour);
  display.print(":");
  if(timeinfo->tm_min<10)
  display.print(0);
   display.print(timeinfo->tm_min);
  display.print(":");
  if(timeinfo->tm_sec<10)
  display.print(0);
  display.print(timeinfo->tm_sec);
  Serial.printf("현재시간:%d시%d%분%d초\n",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
  display.display();
  delay(1000);
  }

  
void countgettogether(int year,int mon,int day){
  
  int y=year;
  int m=mon+1;
  int d=day;                                                //현재 년월일
  int t_sum = 0;                                        //살아온날의 합
  int i;

 

  //살아온 날의 합 계산
  for (i = 115; i < y; i++)
  {
    t_sum += date_sum(i, 12, 31);
  }
  t_sum += date_sum(y, m, d);                        //현재까지 날짜 더함
  t_sum -= date_sum(115,11,6);        //생년1월1일부터 태어난 날까지 합을 빼줌

  

   c_result=t_sum;
  }
  int test_leap_year(int year)
{
  if (year % 4 == 0) {
    if (year % 100 == 0) {
      if (year % 400 == 0)
        return 0;                        //윤년
      else
        return 1;
    }
    else
      return 0;                                //윤년
  }
  else
    return 1;                                        //평년        
}

int date_sum(int y, int m, int d)
{
  int sum = 0;
  int i;
  int test = test_leap_year(y);

  for (i = 1; i < m; i++)
  {
    if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
      sum += 31;
    else if (i == 2)
    {
      if (test == 1)                        //해당 연도가 평년일 경우
        sum += 28;
      else
        sum += 29;                //해당 연도가 윤년일 경우
    }
    else
      sum += 30;
  }
  sum += d;                                                //오늘 날짜 더함
  return sum;
}
