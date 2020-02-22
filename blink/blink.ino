#define PIN_LED 9

void setup()
{
  digitalWrite(PIN_LED, 0);
}

void loop()
{
  digitalWrite(PIN_LED, 1);
  delay(1000);
  digitalWrite(PIN_LED, 0);
  delay(1000);
  digitalWrite(PIN_LED, 1);
}
