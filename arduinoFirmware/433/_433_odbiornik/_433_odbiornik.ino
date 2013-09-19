// Include VirtualWire library
#include <VirtualWire.h>
 
// Pins definition
const int led_pin = 13;
// const int transmit_pin = 12;
const int receive_pin = 47;
 
void setup()
{
   // Init
   delay(1000);
   Serial.begin(9600); // Debugging only
   Serial.println("setup");
 
   // Initialise the IO and ISR
   vw_set_rx_pin(receive_pin);
   vw_setup(2000); // Transmission rate
 
   // Start the receiver PLL
   vw_rx_start();
 
   // Set LED pin
   pinMode(led_pin, OUTPUT);
}
 
void loop()
{
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;
 
   // Check if a message was received
   if (vw_get_message(buf, &buflen))
   {
   // Flash a light to show received good message
   digitalWrite(led_pin, HIGH);
   
   char rcv[12];
   
   for (int i = 0; i < buflen; i++)
   {
     rcv[i] = char(buf[i]);
   }
   
   String received = String(rcv);
   Serial.println(received);
   
   digitalWrite(led_pin, LOW);
   }
}
