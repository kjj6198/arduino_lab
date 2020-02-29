#include "Arduino.h"
#include "dht.h"
#include <string.h> //needed for memcpy

void Dht::blockUntil(int state)
{
  while (digitalRead(DHT_PIN) != state)
  {
  }
}

DhtResult *Dht::get()
{
  // we're sending signal!
  digitalWrite(DHT_PIN, 0);
  // Keep low for at least 18ms
  delay(19);
  digitalWrite(DHT_PIN, 1);
  // After 20-40us DHT will pull the signal low
  pinMode(DHT_PIN, INPUT);
  /**
   * Receive the response from the controller
   */
  // Waiting for DHT to pull low
  blockUntil(LOW); // 80us response
  // Waiting for DHT to pull high
  blockUntil(HIGH); // 80us response
  // Waiting for DHT to pull low (start sending data)
  blockUntil(LOW); // 50us
  /**
   * Receive the data from the controller
   */
  int dataSize = 40;
  // 0 = HUMIDITY
  // 1 = HUMIDITY DECIMAL
  // 2 = TEMP
  // 3 = TEMP DECIMAL
  // 4 = PARITY
  int index = 0;
  int data[5];
  memset(data, 0, sizeof(int) * 5);
  for (auto i = 0; i < dataSize; i++)
  {
    if (i > 0 && i % 8 == 0)
      index++;
    // First bit takes 50us
    blockUntil(HIGH);
    auto timeS = micros();
    // Between 26us/28us bit = 0
    // 70us bit = 1
    blockUntil(LOW);
    auto timeE = micros();
    auto result = timeE - timeS > 60 ? 1 : 0;
    data[index] = (data[index] << 1) + result;
  }
  // Reset to high
  pinMode(DHT_PIN, OUTPUT);
  digitalWrite(DHT_PIN, 1);
  // Display all received bytes
  /*
   * Data  consists  of decimal  and  integral  parts.  
   * A  complete  data  transmission  is 40bit,  and  the sensor sends higher data bitfirst. 
   * Data format:8bit integral 
   * RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data + 8bit check sum. 
   * If the data transmission is right,the check-sum should be the last 8bit of "8bit integral RH data+8bit decimal RHdata+8bit integral T data+8bit decimal T data".
   */
  auto humidity = data[0];
  auto humidityDec = data[1];
  auto temp = data[2];
  auto tempDec = data[3];
  auto parity = data[4];
  // Check parity
  if (humidity + humidityDec + temp + tempDec != parity)
    return NULL;
  auto result = new DhtResult();
  result->humidity = humidity;
  result->humidityDec = humidityDec;
  result->temperature = temp;
  result->temperatureDec = tempDec;
  return result;
}