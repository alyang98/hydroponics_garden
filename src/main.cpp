#include <Arduino.h>
#include <L293DMotor.h>

//https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

L293DMotor* nutrients; 

void setup() {
  nutrients = new L293DMotor(23, 24); //nutrients connected to pin
  Serial.begin(9600);
}

void loop() {
  
  nutrients->testMotor();
}