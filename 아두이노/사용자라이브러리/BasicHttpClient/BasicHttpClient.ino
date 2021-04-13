/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
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
void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);
// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("U+Net16C5", "1C18047287");
// wait for WiFi connection
delay(10000);
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://apis.data.go.kr/1360000/VilageFcstInfoService/getVilageFcst?serviceKey=7503qUB6FNb%2BuC5jrw1iycVdkNUroYZogV7Nav12eN5SdqjGsXoGzWv1OSJn4D7FTFHDfGgWas%2FQVJbUF9T30g%3D%3D&numOfRows=50&&base_date=20200417&base_time=0200&nx=60&ny=121&dataType=JSON")) {  // HTTP


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
  display.setTextColor(WHITE);
display.setTextSize(1);
display.setCursor(0,27);
  display.clearDisplay();
//  Serial.println(doc["response"]["body"]["numOfRows"].as<long>());
  for(int i=0;i<doc["response"]["body"]["numOfRows"].as<long>();i++){
     if(strcmp("TMN",doc["response"]["body"]["items"]["item"][i]["category"].as<char *>())==0||strcmp("TMX",doc["response"]["body"]["items"]["item"][i]["category"].as<char *>())==0){
//   Serial.println(doc["response"]["body"]["items"]["item"][i]["fcstValue"].as<char *>());
display.print(doc["response"]["body"]["items"]["item"][i]["fcstValue"].as<char *>());
display.print("    ");
display.display();
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
}

void loop() {
  

  
}
