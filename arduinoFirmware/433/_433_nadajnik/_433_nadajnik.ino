// Include VirtualWire library
#include <VirtualWire.h>
#include "DHT.h"
#include <stdlib.h>


#define DHTPIN 2 // what pin we're connected to
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
// Define pins
const int led_pin = 13;
const int transmit_pin = 12;
// const int sensor_pin = 7;
 
int sensor_value;
 
void setup()
{
   // Init
   vw_set_tx_pin(transmit_pin);
   vw_setup(2000); // Transmission rate
   pinMode(led_pin, OUTPUT);
   // pinMode(sensor_pin,INPUT);
   dht.begin();
   
   //Serial.begin(9600);  <- for debug 
}
 
void loop()
{
   // dht part:
   float h = dht.readHumidity();
   float t = dht.readTemperature();
    
   if (isnan(t) || isnan(h)) {
     ;
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
     //Serial.println(message);    <- for debug
     
     digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
     vw_send((uint8_t *)message, 12);
     vw_wait_tx(); // Wait until the whole message is gone
     digitalWrite(led_pin, LOW);
     
     delay(1000);
   }
 }
