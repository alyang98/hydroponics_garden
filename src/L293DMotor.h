#pragma once
#include <Arduino.h>
#include<stdio.h>
#include<stdlib.h>
#include <analogWrite.h>

class L293DMotor {
public:

	L293DMotor(int f = 0, int b = 0) {
		x = f; //pin 1/3
		y = b; //pin 2/4
		pinMode(x, OUTPUT);
		pinMode(y, OUTPUT);
	}

	// v is from -1 to 1
	void power(float v) {
		
		//v = min(v, 1);
        if (v >= 1) 
            v = 1;
		//v = max(v, -1);
        if(v <= 0)
            v = 0;//should not go the other direction

		if (v < 0) {
			analogWrite(x, 0);
			analogWrite(y, -v * 255);
		}

		else if (v > 0) {
			analogWrite(y, 0);
			analogWrite(x, v * 255);
		}
		else {
			analogWrite(x, 0);
			analogWrite(y, 0);
		}
	}

	void powerTime(float v, int ms) {
		power(v);
		delay(ms);
	}
	void testMotor(int delay_ms = 500) {
		powerTime(1, delay_ms);
		powerTime(0, delay_ms);
		powerTime(-1, delay_ms);
		powerTime(0, delay_ms);
	}
private:
	int x;
	int y;
};




