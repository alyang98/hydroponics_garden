#include <Arduino.h>
#include <L293DMotor.h>

L293DMotor* nutrients;

void setup() {
  nutrients = new L293DMotor(5, 18); //nutrients connected to pin
}

void loop() {
  // put your main code here, to run repeatedly:
  //testMotor();
}