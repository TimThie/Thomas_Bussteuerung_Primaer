#include <Arduino.h>
#include "program.h"
#include "appTemperature.h"

#define version_major 1
#define version_minor 0
#define version_patch 0

void setup()
{
  pinMode(SLEEPLED_PIN, OUTPUT);
  sensor_init();
#if (DEBUG == 1)
  debugInit();
#endif
}

void loop()
{
  program();
}