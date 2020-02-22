#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

byte rowPins[ROWS] = {39, 41, 43, 45}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {47, 49, 51, 53}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

RTC_DS1307 rtc;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }

  if (!rtc.isrunning())
  {
    Serial.println("RTC lost power, lets set the time!");
    // set to computer time
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop()
{
  DateTime now = rtc.now();

  char buffer[9] = "";
  lcd.setCursor(0, 0);
  sprintf(buffer, "%02d/%02d/%02d", now.year(), now.month(), now.day());
  lcd.print(buffer);
  lcd.setCursor(0, 1);
  sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  lcd.print(buffer);

  char customKey = customKeypad.getKey();
  if (customKey)
  {
    Serial.println(customKey);
  }

  if (now == DateTime(2020, 2, 16, 23, 4, 00))
  {
    lcd.clear();
    lcd.print("times up!!");
    delay(1000);
  }
}
