//#define DEBUG_ESP_HTTP_CLIENT 1
//#define DEBUG_ESP_PORT Serial

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

extern "C"{ 
  #include "user_interface.h" 
}
 
os_timer_t mTimer;
bool _timeout = false;
const char* ssid = "******";
const char* password = "*******";
float temp = 0.0;

void tCallback(void *tCall){
    _timeout = true;
}

void usrInit(void) {
    os_timer_setfn(&mTimer, tCallback, NULL);
    os_timer_arm(&mTimer, 10000, true);
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting "); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); 
  }
  Serial.print("\nConnected. My IP: "); 
  Serial.println(WiFi.localIP());
  usrInit();
}

void loop() {
  if (_timeout){
      temp = getTempCelsius(A0);
      HTTPClient http;
      String url = "https://api.thingspeak.com/update?api_key=VXTXNK09FJEQIE6F&field1=";
      url += String(temp);
      http.begin(url,"78:60:18:44:81:35:BF:DF:77:84:D4:0A:22:0D:9B:4E:6C:DC:57:2C"); //https://www.grc.com/fingerprints.htm
      int httpCode = http.GET();
      Serial.println(httpCode);
      if(httpCode > 0) {
        Serial.print("[HTTP] GET... code: ");
        Serial.println(httpCode);
        if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.print("[HTTP] GET... data: ");
          Serial.println(payload);
        } else {
          Serial.print("[HTTP] GET... failed, error: ");
          Serial.println(http.errorToString(httpCode).c_str());
        }
      }
       http.end();
      _timeout = false;
  }
}

float getTempCelsius(int analogPin) {
  int rawvoltage = analogRead(analogPin);
  float millivolts = (rawvoltage*3.3/1024.0);
  float celsius = (millivolts/0.01) - 273.15;
  return celsius;
}
