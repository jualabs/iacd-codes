struct record { 
	unsigned long ts;
	float temperature;
	float humidity;
} records[5];

unsigned int insertionPos = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int i = 0;
  
  records[insertionPos].ts = millis();
  records[insertionPos].temperature = (float) random(0, 50);
  records[insertionPos].humidity = (float) random(0, 100);
  
  insertionPos++;
  if(insertionPos == 5) insertionPos = 0;
  
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