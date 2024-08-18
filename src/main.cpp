#include <Arduino.h>

#include "pinAssignment.h"
#include "drvLED.h"
#include "drvSleepCtl.h"

#define SLEEP_TIMER_MS 60000
#define LED_TOGGLE_TIME_MS 2500

uint32_t led_timer;
uint32_t sleep_timer;

DrvLED testLED(LED_PIN);
DrvSleepCtrl sleepCtrl(WAKEUP_PIN);

void setup()
{
  Serial.begin(9600);

  led_timer = millis();
  sleep_timer = millis();
}

void loop()
{
  if (millis() - led_timer > LED_TOGGLE_TIME_MS)
  {
    led_timer = millis();
    testLED.toggle();
    if (millis() - sleep_timer > SLEEP_TIMER_MS)
    {
      sleepCtrl.gotoSleep();
      sleep_timer = millis();
    }
  }
}