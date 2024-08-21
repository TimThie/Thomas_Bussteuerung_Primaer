#ifndef PROGRAM_H
#define PROGRAM_H

#include "pinAssignment.h"
#include "drvLED.h"
#include "drvSleepCtl.h"
#include "drvButton.h"

#define SLEEP_TIMER_MS 5000

void program();
void sleepTask();
void mainLightTask();
void trunkLidTask();

#endif