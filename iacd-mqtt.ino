#include <ESP8266WiFi.h>
#include <PubSubClient.h>

extern "C"{ 
  #include "user_interface.h" 
}
 
os_timer_t mTimer;
bool _timeout = false;
const char* ssid = "XXXX";
const char* password = "XXXX";
const char* mqtt_server = "XXXX";
const char* clientID = "nodemcu";
const char* topic = "temp";
const char* mqttuser = "XXXX";
const char* mqttpass = "XXX";
const int port = XXXXX;

float temp = 0.0;
char temp_c[20];
WiFiClient TempClient;
PubSubClient mqttclient(TempClient);

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
  mqttclient.setServer(mqtt_server, port);
  usrInit();
}

void loop() {
if (!mqttclient.connected()) {
    mqtt_connection();
  }
  if (_timeout){
      temp = getTempCelsius(A0);
      dtostrf(temp, 2, 2, temp_c);
      mqttclient.publish(topic, temp_c);
     _timeout = false;
  }
  mqttclient.loop();
}

void mqtt_connection() {
  while (!mqttclient.connected()) {
    Serial.print("Attempting MQTT connection ");
    if (mqttclient.connect(clientID,mqttuser,mqttpass)) {
      Serial.println("Connected!");
    } else {
      Serial.print(".");
      delay(1000);
    }
  }
}

float getTempCelsius(int analogPin) {
  int rawvoltage = analogRead(analogPin);
  float millivolts = (rawvoltage*3.3/1024.0);
  float celsius = (millivolts/0.01) - 273.15;
  return celsius;
}
