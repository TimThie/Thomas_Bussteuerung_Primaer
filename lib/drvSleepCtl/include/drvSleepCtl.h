#pragma once
#include <Arduino.h>
#include <avr/sleep.h>
#include "pinAssignment.h"
#include <avr/interrupt.h>

volatile bool pinInterrupt = false;
void gotoSleepMS(uint32_t);
void setupSleepTask();