#include <Arduino.h>
#include "program.h"
#include "appTemperature.h"

void setup()
{
  pinMode(SLEEPLED_PIN, OUTPUT);
  sensor_init();
#if (DEBUG == 1)
  Serial.begin(9600);

#endif
}

void loop()
{
  program();
}