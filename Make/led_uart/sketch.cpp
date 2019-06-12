#include <Arduino.h>

void setup() {
  
   Serial.print(" ===================="); 
   GPIO_P3 = 0xAA;
   
   delay (2000);
}

uint32_t i = 0;
uint8_t led_position = 0;

void loop() {

 Serial.print (i);
 i = (i + 1) %(1024);
 Serial.print(" ==================== \n"); 
 delay (600);
 led_position = (led_position + 1) % 8;

 GPIO_P3 = ~(1 << led_position);

}