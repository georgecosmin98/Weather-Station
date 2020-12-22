int countTrueCommand;
int countTimeCommand;
boolean found = false;
volatile int temperature;
volatile int humidity;
volatile int brightness;
volatile int pressure;
volatile int timerCounter = 0;

void setup()
{
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  myDelay_setup();
  ESP8266_setup();
  BME280_setup();
  LCD_setup();
}

void loop()
{
  getDHTvalue();
  getBrightnessValue();
  getBMEvalue();
  LCDrefresh();
  sendAllDataToThingSpeak(temperature, humidity, brightness);
  myDelay(1000);
}
