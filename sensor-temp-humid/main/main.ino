#include <LiquidCrystal.h>
#include "dht.h"

bool ranOnce = false;

// LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
//                 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
LiquidCrystal lcd(/*RS*/ 10,
                  /*RW*/ 9,
                  /*ENABLE*/ 8,
                  /*D0*/ 7,
                  /*D1*/ 6,
                  /*D2*/ 5,
                  /*D3*/ 4);

void setup()
{
  Serial.begin(19200);
  lcd.begin(16, 2);
  // step1. send signal to our DHT
  pinMode(DHT_PIN, OUTPUT);
  digitalWrite(DHT_PIN, 1);
  delay(1000);
}

long levelTime(byte level)
{
  unsigned long time_start = micros();
  long time = 0;
}

void loop()
{
  lcd.setCursor(0, 0);
  // lcd.print("Hello World!");
  delay(1500);
  DhtResult *result = Dht::get();
  if (result == NULL)
  {
    lcd.print("TEMP ERROR");
    return;
  }
  char output[500];
  Serial.println(result->temperature);
  sprintf(output, "TEMP: %d.%d\0", result->temperature, result->temperatureDec);
  lcd.print(output);
  sprintf(output, "HUMID: %d.%d\0", result->humidity, result->humidityDec);
  lcd.setCursor(0, 1);
  lcd.print(output);
}
