#include "DHT.h"
#include<stdlib.h>

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  
  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    
    char hBuffer[7];    
    char tBuffer[7];
    
    dtostrf(h,5,2,hBuffer);
    dtostrf(t,5,2,tBuffer);
    
    String hStr = String(hBuffer);
    String tStr = String(tBuffer);
    
    String combo = String(hStr+";"+tStr);
    
    char message[12];
    combo.toCharArray(message,12);
    
    Serial.println(message);
    //10k is 10s:
    delay(2000);
  }
}
