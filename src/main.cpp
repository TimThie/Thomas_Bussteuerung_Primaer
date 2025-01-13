#include <Arduino.h>
#include "program.h"
#include "appTemperature.h"

void setup()
{
  pinMode(SLEEPLED_PIN, OUTPUT);

  // Change Timer 0 prescaler to 8
  TCCR0B = (TCCR0B & 0b11111000) | 0x02;

  sensor_init();
#if (DEBUG == 1)
  debugInit();
#endif
}

void loop()
{
  program();
}