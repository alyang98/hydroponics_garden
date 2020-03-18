#pragma once
#include <Arduino.h>

#include<stdio.h>
#include<stdlib.h>
#include <analogWrite.h>
#include <math.h>

class pHSensorModule {
public:

	pHSensorModule(int pin) {

		pHSensorPin = pin; 
		pinMode(pHSensorPin, INPUT);

	}

	void getPH(){
		// read the input:
  		int sensorValue = analogRead(pHSensorPin);

		float pHReading = calculatePH(sensorValue);

	  	// print out the value you read:
	  	Serial.println(pHReading);
		delay(300);

	}//end of getPH

	/*
	* Convert the analog reading (which goes from 0 - 4096) to a pH (0 - 14): pH is inverted (14 pH is low voltage) 
	* However, because of rounding errors in the voltage divider circuit, we had to adjust it in code by getting the ratio difference between ideal and actual
	* Then dividing 14 by the ratio to get 14.88
	*/
	float calculatePH(int sensorValue){

		float pHReading = 14.0f - sensorValue * (14.22f / 4096.0f);
		return pHReading;

	}//end of calculatePH

    //https://www.botshop.co.za/how-to-use-a-ph-probe-and-sensor/
	//http://www.baaqii.net/promanage/BU0203%2BBU0481.pdf 
	float getAveragePH(){

	  int avgValue;

	  int buf[10];	//buffer for read analog
	  for(int i=0;i<10;i++)	//Get 10 sample value from the sensor for smooth the value
	  {
	    buf[i]=analogRead(pHSensorPin);  
	    delay(10);
	  }
	  for(int i=0;i<9;i++)	//sort the analog from small to large
	  {
	    for(int j=i+1;j<10;j++)
	    {
	      if(buf[i]>buf[j])
	      {
	        int temp=buf[i]; 
	        buf[i]=buf[j]; 
	        buf[j]=temp;
	      }//end of if  
	    }//end of for 
	  }//end of for
	  avgValue=0;
	  for(int i=2;i<8;i++)	//take the average value of 6 center sample 
	  {
	    avgValue+=buf[i];
	  }
		
	  //float pHValue = 14.0f - (avgValue/6.0f) * (14.88f / 4096.0f);
	  float pHValue = calculatePH(avgValue/6.0f);
	  
	  Serial.print(pHValue,2); 
	  Serial.println(" "); 
		return pHValue;
	}//end pHsensor

private:
	int pHSensorPin;

};