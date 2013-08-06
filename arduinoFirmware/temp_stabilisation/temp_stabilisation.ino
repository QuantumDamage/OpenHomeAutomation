// This Arduino sketch reads DS18B20 "1-Wire" digital
// temperature sensors.
// Tutorial:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-tutorial.html

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 3 on the Arduino
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

DeviceAddress insideThermometer = { 0x28, 0xC6, 0x61, 0x9F, 0x03, 0x00, 0x00, 0x70 };

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  // set the resolution to 10 bit (good enough?)
  sensors.setResolution(insideThermometer, 12);
}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    //Serial.print("C: ");
    Serial.println(tempC);
    //Serial.print("\n");
    //Serial.print(" F: ");
    //Serial.print(DallasTemperature::toFahrenheit(tempC));
  }
}

void loop(void)
{ 
  //10k is 10s
  delay(1000);
  //Serial.print("Getting temperatures...\n\r");
  sensors.requestTemperatures();
  
  //Serial.print("Inside temperature is: ");
  printTemperature(insideThermometer);
  //Serial.print("\n\r\n\r");
  
  
  
}

