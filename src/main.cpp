#include <Arduino.h>

// #include "./../components/drvSleepCtl/include/drvSleepCtl.h"
#include "pinAssignment.h"
#include "drvLED.h"
// #include "drvSleepCtl.h"

uint32_t led_timer;
DrvLED testLED(LED_PIN);
void setup()
{
  Serial.begin(9600);
  led_timer = millis();
}

void loop()
{
  if (millis() - led_timer > 2500)
  {
    led_timer = millis();
    testLED.toggle();
    // gotoSleepMS(); /* GOTO SLEEP WHEN READY NOT FINISHED */
  }
}