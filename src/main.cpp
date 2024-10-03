#include <Arduino.h>

#include "program.h"

void setup()
{
  pinMode(SLEEPLED_PIN, OUTPUT);
}

void loop()
{
  program();
}