typedef struct _record { 
	unsigned long ts;
	float temperature;
	float humidity;
} record;

record records[5];
record *pRecords, *pBase;
unsigned int iterCounter = 0;

void setup()
{
  Serial.begin(9600);
  pRecords = records;
  pBase = records;
}

void loop()
{
  int i = 0;
  
  pRecords->ts = millis();
  pRecords->temperature = (float) random(0, 50);
  pRecords->humidity = (float) random(0, 100);
  
  pRecords++;
  iterCounter++;
  if(iterCounter == 5) {
    pRecords = pBase;
    iterCounter = 0; 
  }
  
  Serial.println("***** records *****");
  for (i = 0; i < 5; i++) {
    Serial.print(i, DEC);
    Serial.print(" - ts: "); 
    Serial.print(records[i].ts, DEC);
  	Serial.print(", temperature: "); 
    Serial.print(records[i].temperature, 2);
   	Serial.print(", humidity: "); 
    Serial.println(records[i].humidity, 1);
  }
  delay(2000);
}