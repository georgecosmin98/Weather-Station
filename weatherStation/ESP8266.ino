#include <SoftwareSerial.h>

#define RX_pin 2
#define TX_pin 3

String AP = "Telekom-6DA1";
String PASS = "A2ZSYCM2PVLKR";
String API = "ZOPP08IZU17W667D";
String HOST = "api.thingspeak.com";
String PORT = "80";

SoftwareSerial esp8266(RX_pin,TX_pin);

void ESP8266_setup() 
{
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT", 5, "OK");
  sendCommand("AT+CWMODE=1", 5, "OK");
  sendCommand("AT+CWJAP=\"" + AP + "\",\"" + PASS + "\"", 20, "OK");
}

void sendAllDataToThingSpeak(int tempValue, int humidityValue, int brightnessValue)
{

  String getData = "GET /update?api_key=" + API + "&field1=" + String(tempValue) + "&field2=" + String(humidityValue) + "&field3=" + String(brightnessValue);
  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
  sendCommand("AT+CIPSEND=0," + String(getData.length() + 4), 4, ">");
  esp8266.println(getData);
  countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0", 5, "OK");
}

void sendCommand(String command, int maxTime, char readReplay[])
{
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while (countTimeCommand < (maxTime * 1))
  {
    esp8266.println(command);     //at+cipsend
    if (esp8266.find(readReplay)) //ok
    {
      found = true;
      break;
    }

    countTimeCommand++;
  }

  if (found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }

  if (found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }

  found = false;
}
