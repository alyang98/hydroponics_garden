#include <Arduino.h>
#include <L293DMotor.h>
#include <pHSensorModule.h>
#include <WiFi.h>

//https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

void testAllMotors();

L293DMotor *pHUpper, *pHLower;
pHSensorModule *pH;
WiFiServer server(2025);

void setup()
{

  pHUpper = new L293DMotor(22);
  pHLower = new L293DMotor(23);
  pH = new pHSensorModule(35);

  Serial.begin(9600);

  WiFi.softAP("SmartPlanter", "smartyb0i");
  server.begin();

  //Serial.printf("%s\n",WiFigatewayIP()); https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html#set-up-network

} //end setup

void loop()
{

  //testAllMotors();

  WiFiClient client = server.available();
  if (client)
  {
    while(!client.available()){
      delay(10);
    }

    int client_read = client.read();
    switch (client_read)
    {
    case 1: // pH
    {
      float newph = pH->getAveragePH();
      uint8_t byteph = (uint8_t)((int)(newph / 14.0f * 256.0f) % 256); //convert to byte
      client.write(byteph);
      client.flush();
      break;
    }

    case 2: // temp
    {
      break;
    }
    }

  } //end of if

} //end main loop

void testAllMotors()
{

  pHUpper->testMotor();
  pHLower->testMotor();

} //end testAllMotors
