int touchSensor = 15;  // 터치센서 핀 설정
int a=0;
 
void setup() {
  Serial.begin(115200);
  pinMode(touchSensor, INPUT);
  
}
 
void loop() {
  //터치값 읽음
  int touchValue = digitalRead(touchSensor);
   
  if (touchValue == HIGH){      // 터치됨
    Serial.println("TOUCHED");
    a++;
    Serial.println(a);

  } else {                      //터치 안됨
    Serial.println("NOT TOUCHED");
  }
 
  delay(1000);
}
