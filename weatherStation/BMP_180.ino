#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 bmp180;

void BMP180_setup() 
{
  bmp180.begin();
}

void getBMPvalue() 
{
  char status;
  double pres, temp;
  status = bmp180.startTemperature();
  if (status != 0) 
  {
    delay(1000);
    status = bmp180.getTemperature(temp);
    if (status != 0) 
    {
      status = bmp180.startPressure(3);
      if (status != 0) 
      {
        delay(status);
        status = bmp180.getPressure(pres,temp);
        if (status != 0)
           pressure = pres * 0.75006157584566;
      }
    }
  }
}
