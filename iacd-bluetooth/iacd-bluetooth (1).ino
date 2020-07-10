#include "DHT.h"
#include <TimeAlarms.h>
#define DHTPIN D1
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  Alarm.timerRepeat(2, coleta);
}
 
void loop()
{
  Alarm.delay(1000);
}

void coleta() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Leitura do DHT falhou!");
    return;
  }
  Serial.print("Temperatura:");
  Serial.println(temp);
}
