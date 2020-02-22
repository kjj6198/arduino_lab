/**
 * Copyright (C) 2020 Henry - All Rights Reserved
 */
#include "RTClib.h"
#include <LiquidCrystal.h>
#include <IRremote.h>
#include <SimpleDHT.h>
// 自己的

// read()
// setPinInputMode()
// setPin()
// getBitmask()
// getPort()
// levelTime()
// bits2byte()
// parse()
// read2()
// sample()

#define DHT_PIN 7

SimpleDHT11 dht11(DHT_PIN);

// const byte ROWS = 4;
// const byte COLS = 4;
// char hexaKeys[ROWS][COLS] = {
//     {'1', '2', '3', 'A'},
//     {'4', '5', '6', 'B'},
//     {'7', '8', '9', 'C'},
//     {'*', '0', '#', 'D'},
// };
// byte rowPins[ROWS] = {39, 41, 43, 45}; //connect to the row pinouts of the keypad
// byte colPins[COLS] = {47, 49, 51, 53}; //connect to the column pinouts of the keypad
// Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

RTC_DS1307 rtc;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(115200);

  lcd.begin(16, 2);
}

// #define NEC 1
// #define SONY 2
// #define RC5 3
// #define RC6 4
// #define DISH 5
// #define SHARP 6
// #define PANASONIC 7
// #define JVC 8
// #define SANYO 9
// #define MITSUBISHI 10
// #define SAMSUNG 11
// #define LG 12
// #define UNKNOWN -1
void loop()
{
  byte humidity;
  byte temperature;
  int err;
  lcd.setCursor(0, 0);
  delay(1500);

  dht11.read(&temperature, &humidity, NULL);

  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print((int)temperature);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Hum:");
  lcd.print((int)humidity);

  delay(1000);

  lcd.setCursor(0, 1);
}

// https://forum.arduino.cc/index.php?topic=554738.0
