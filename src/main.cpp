#include <Arduino.h>

#include "pinAssignment.h"
#include "drvLED.h"
#include "drvSleepCtl.h"
#include "drvButton.h"

#define SLEEP_TIMER_MS 5000

uint32_t led_timer;
uint32_t sleep_timer;

DrvLED testLED(LED_PIN);
DrvSleepCtrl sleepCtrl(WAKEUP_PIN);
DrvButton hauptlicht(HAUPTLICHT_PIN, LOW);

void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  led_timer = millis();
  sleep_timer = millis();
}

void loop()
{
  if (hauptlicht.wasClicked())
  {
    Serial.println("Triggered NO DIM");
    testLED.setMaxBrightness(255);
    testLED.toggle();
  }
  digitalWrite(LED_BUILTIN, HIGH);
  if (millis() - sleep_timer > SLEEP_TIMER_MS)
  {
    digitalWrite(LED_BUILTIN, LOW);
    sleepCtrl.gotoSleep();
    sleep_timer = millis();
  }
}