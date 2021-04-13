String line = "{\"coord\":{\"lon\":126.98,\"lat\":37.57}"
              ",\"weather\":[{\"id\":701,\"main\":\"Mist\",\"description\":\"mist\",\"icon\":\"50n\"}]"
              ",\"base\":\"stations\",\"main\":"
              "{\"temp\":283.7,\"pressure\":1020,\"humidity\":100,\"temp_min\":281.15,\"temp_max\":286.15}"
              ",\"visibility\":1200,\"wind\":{\"speed\":0.5,\"deg\":40}"
              ",\"clouds\":{\"all\":75},\"dt\":1572715825,\"sys\":"
              "{\"type\":1,\"id\":5501,\"country\":\"KR\",\"sunrise\":1572731897,\"sunset\":1572769974}"
              ",\"timezone\":32400,\"id\":1835848,\"name\":\"Seoul\",\"cod\":200}";

void setup() {
  Serial.begin(115200);
  Serial.println(line);
  String description = json_parser(line, "description");
  Serial.println(description);
  String pressure = json_parser(line, "pressure");
  Serial.println(pressure);
  String wind = json_parser(line, "speed");
  Serial.println(wind);
  String Temp = json_parser(line, "temp");
  Serial.println(Temp);
}

void loop() {

}

String json_parser(String s, String a) { 
  String val;
  if (s.indexOf(a) != -1) {
    int st_index = s.indexOf(a);
    int val_index = s.indexOf(':', st_index);
    if (s.charAt(val_index + 1) == '"') {
      int ed_index = s.indexOf('"', val_index + 2);
      val = s.substring(val_index + 2, ed_index);
    }
    else {
      int ed_index = s.indexOf(',', val_index + 1);
      val = s.substring(val_index + 1, ed_index);
    }
  } 
  else {
    Serial.print(a); Serial.println(F(" is not available"));
  }
  return val;
}
