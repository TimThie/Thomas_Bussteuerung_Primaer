#include <Arduino.h>

#include "pinAssignment.h"
#include "drvSleepCtl.h"

int myFunction(int, int);
uint32_t led_timer;
uint32_t sleep_timer;
bool ledState = LOW;
DrvSleepCtrl SleepCtrl(WAKEUP_PIN);

void setup()
{
  Serial.begin(9600);
  led_timer = millis();
  pinMode(LED_PIN, OUTPUT);
  pinMode(WAKEUP_PIN, INPUT_PULLUP);
  sleep_timer = millis();
}

void loop()
{
  if (millis() - led_timer > 1000)
  {
    led_timer = millis();
    digitalWrite(LED_PIN, ledState);
    ledState = !ledState;
    Serial.println("LED Toggled");

    if (millis() - sleep_timer > 10000)
    {
      Serial.println("Good Night");
      SleepCtrl.gotoSleep(); /* GOTO SLEEP WHEN READY NOT FINISHED */
      sleep_timer = millis();
    }
  }
}

int myFunction(int x, int y)
{
  return x + y;
}