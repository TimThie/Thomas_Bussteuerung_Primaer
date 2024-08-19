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

  pinMode(LIGHTSWITCH1_PIN, INPUT);
  pinMode(LIGHTSWITCH2_PIN, INPUT);

  led_timer = millis();
  sleep_timer = millis();
}

void loop()
{
  uint8_t read1 = digitalRead(LIGHTSWITCH1_PIN);
  uint8_t read2 = digitalRead(LIGHTSWITCH2_PIN);
  Serial.println(read1);
  Serial.println(read2);
  if (read1 == HIGH)
  {
    Serial.println("Triggered NO DIM");
    testLED.setMaxBrightness(255);
    testLED.toggle();
  }
  if (read2 == HIGH)
  {
    Serial.println("Triggered DIM");
    testLED.setMaxBrightness(10);
    testLED.toggle();
  }
  if (millis() - sleep_timer > SLEEP_TIMER_MS)
  {
    sleepCtrl.gotoSleep();
    sleep_timer = millis();
  }
}