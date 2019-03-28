#include <ESP8266WiFi.h>
#include "DHT.h"
#include <TimeAlarms.h>
#define DHTPIN D1
#define DHTTYPE DHT22

extern "C"{ 
  #include "user_interface.h" 
}
 
const char* ssid = "iacd";
const char* password = "iacd1234";
WiFiServer server(8000);
WiFiClient TempClient;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  conectar();
  server.begin();
  //server.setNoDelay(true);
  Alarm.timerRepeat(2, coleta);
}

void loop() {
  if (server.hasClient()){
    if (!TempClient || !TempClient.connected()) {
      TempClient = server.available();
    }
  }
  Alarm.delay(100);
  //yield();
}

void conectar() {
  WiFi.begin(ssid, password);
  Serial.print("\nConectando "); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); 
  }
  Serial.print("\nConectado. Meu IP: "); 
  Serial.println(WiFi.localIP());  
}

void coleta() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Leitura do DHT falhou!");
    return;
  }
  if (TempClient && TempClient.connected()){
    TempClient.print("Temperatura:");
    TempClient.println(temp);
  }
  yield(); 
}
