#include <OneWire.h> 
#include <DallasTemperature.h>

#define DS_pin A1

OneWire oneWire(DS_pin); 
DallasTemperature tempSensor(&oneWire);

void DS18B20_setup() 
{ 
  tempSensor.begin(); 
} 

void getExternalTempValue()
{
  external_temp = tempSensor.getTempCByIndex(0); 
}
