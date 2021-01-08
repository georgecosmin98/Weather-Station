int countTrueCommand;
int countTimeCommand;
boolean found = false;
volatile double temperature;
volatile int humidity;
volatile int brightness;
volatile double pressure;
volatile double external_temp;
volatile int timerCounter = 0;

void setup()
{
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  myDelay_setup();
  ESP8266_setup();
  BMP180_setup();
  DS18B20_setup();
  LCD_setup();
}

void loop()
{
  temperature = -1;
  while(!verifyDataIntegrity())
  {
    getDHTvalue();
    getBrightnessValue();
    getBMPvalue();
    getExternalTempValue();
    myDelay(2000); 
  }
  sendAllDataToThingSpeak(temperature, humidity, brightness, pressure, external_temp);
  LCDrefresh();
}
