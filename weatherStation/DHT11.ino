#include <dht.h>

#define DHT_pin    A0

dht DHT;

void getDHTvalue()
{
  DHT.read11(DHT_pin);
  temperature = DHT.temperature;
  humidity = DHT.humidity;
}
