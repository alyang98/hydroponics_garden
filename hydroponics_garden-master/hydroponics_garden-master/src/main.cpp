#include <Arduino.h>
#include <L293DMotor.h>

//https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

void pHsensor();
void testAllMotors();

L293DMotor *nutrients, *pHUpper, *pHLower; 

void setup() {

  nutrients = new L293DMotor(23); //nutrients connected to pin
  pHUpper = new L293DMotor(22);
  pHLower = new L293DMotor(19);

  pinMode(14,INPUT);

  Serial.begin(9600);

}//end setup

void loop() {
  
  //testAllMotors();
  pHsensor();

}//end main loop

//https://github.com/alyang98/omnibot/blob/master/sketch_dec01a/L293DMotor.h
void testAllMotors(){
  nutrients->testMotor();
  pHUpper -> testMotor();
  pHLower -> testMotor();

}//end testAllMotors

//https://www.botshop.co.za/how-to-use-a-ph-probe-and-sensor/
//http://www.baaqii.net/promanage/BU0203%2BBU0481.pdf 
void pHsensor(){

  // read the input on analog pin 0:
  //  int sensorValue = analogRead(14);

  // Convert the analog reading (which goes from 0 - 4096) to a pH (0 - 14): pH is inverted (14 pH is low voltage) 
  //However, because of rounding errors in the voltage divider circuit, we had to adjust it in code by getting the ratio difference between ideal and actual 7/7.21 = 0.90673
  //Then dividing 14/0.90673 
  //  float pHReading = 14.0f - sensorValue * (15.44f / 4096.0f);

  // print out the value you read:
  //  Serial.println(pHReading);

  //delay(300);

  int avgValue;

  int buf[10];	//buffer for read analog
  for(int i=0;i<10;i++)	//Get 10 sample value from the sensor for smooth the value
  {
    buf[i]=analogRead(14); 
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

  float pHValue = 14.0f - (avgValue/6.0f) * (15.44f / 4096.0f);

  Serial.print(pHValue,2); 
  Serial.println(" "); 

}//end pHsensor