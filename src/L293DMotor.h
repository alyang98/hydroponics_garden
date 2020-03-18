#pragma once
#include <Arduino.h>
#include<stdio.h>
#include<stdlib.h>
#include <analogWrite.h>
#include <math.h>

//https://github.com/alyang98/omnibot/blob/master/sketch_dec01a/L293DMotor.h
class L293DMotor {
public:

	L293DMotor(int f) {
		x = f; 
		pinMode(x, OUTPUT);

	}

	// v is from -1 to 1
	void power(float v) {
		
		v = min(v, 1.0f);
		v = max(v, 0.0f);
		
		//Serial.printf("x %d v %f\n", x, v);
		analogWrite(x, v*255);
	}

	void powerTime(float v, int ms) {
		power(v);
		delay(ms);
	}
	void testMotor(int delay_ms = 500) {
		powerTime(1, delay_ms);
		powerTime(0, delay_ms);

	}
private:
	int x;

};




