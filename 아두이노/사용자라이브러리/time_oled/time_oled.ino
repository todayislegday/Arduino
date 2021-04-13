#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <time.h>

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



int timezone = 9;


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

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  Serial.println("\nConnecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(1000);

  }

  configTime(timezone * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.println("\nWaiting for time");

  while (!time(NULL)) {

    Serial.print(".");

    delay(1000);

  }

  Serial.println("");

}



void loop() {
  time_t now = time(NULL);
  struct tm* timeinfo;
  timeinfo=localtime(&now);
  display.setCursor(2,0);
  display.println("sunny");
  display.println("");
  display.print(timeinfo->tm_hour);
  display.print(":");
   display.print(timeinfo->tm_min);
  display.print(":");
  display.print(timeinfo->tm_sec);
  display.display();
  Serial.printf("현재시간:%d시%d%분%d초\n",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
  delay(1000);
  display.clearDisplay();
  
}
