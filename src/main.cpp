#include <Arduino.h>

// #include "./../components/drvSleepCtl/include/drvSleepCtl.h"
#include "pinAssignment.h"
#include "drvSleepCtl.h"

int myFunction(int, int);
uint32_t led_timer;
bool ledState = LOW;

void setup()
{
  Serial.begin(9600);
  led_timer = millis();
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  if (millis() - led_timer > 1000)
  {
    led_timer = millis();
    digitalWrite(LED_PIN, ledState);
    ledState = !ledState;

    // gotoSleepMS(); /* GOTO SLEEP WHEN READY NOT FINISHED */
  }
}

int myFunction(int x, int y)
{
  return x + y;
}