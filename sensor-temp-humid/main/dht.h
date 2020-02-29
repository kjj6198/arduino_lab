#pragma once
#define DHT_PIN 2

struct DHTData
{
  float humidity;
  float temperature;
  byte raw_data[40];
};

struct DhtResult
{
  unsigned char humidity;
  unsigned char humidityDec;
  unsigned char temperature;
  unsigned char temperatureDec;
};

class Dht
{
public:
  static DhtResult *get();

private:
  static void Dht::blockUntil(int state);
};