#include <Wire.h>
#include "SparkFunBME280.h"

BME280 myBMEsensor;

void BME280_setup()
{
  Wire.begin();
  myBMEsensor.setI2CAddress(0x76); 
  if(myBMEsensor.beginI2C() == false)
     Serial.println("Sensor BME80 connect failed !");
}

void getBMEvalue()
{
  pressure = myBMEsensor.readFloatPressure()/100;
}
