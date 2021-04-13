#include <ESP8266WiFi.h>
#include <time.h>



const char* ssid = "U+Net16C5";

const char* password = "1C18047287";



int timezone = 9;





void setup() {

  Serial.begin(115200);

  Serial.setDebugOutput(true);



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
  Serial.printf("현재시간:%d시%d%분%d초\n",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
  delay(1000);

}
