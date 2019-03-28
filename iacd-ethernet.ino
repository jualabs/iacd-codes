#include <Ethernet.h>
#include "DHT.h"
#include <TimeAlarms.h>
#define DHTPIN 2
#define DHTTYPE DHT22

// Enter a MAC address for your controller below.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server(8000);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Ethernet.begin(mac);
  Serial.print("My address:");
  Serial.println(Ethernet.localIP());
  server.begin();
  Alarm.timerRepeat(2, coleta);
}

void loop() {
  Alarm.delay(1000);
}

void coleta() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Leitura do DHT falhou!");
    return;
  }
  server.print("Temperatura:");
  server.println(temp);
}
