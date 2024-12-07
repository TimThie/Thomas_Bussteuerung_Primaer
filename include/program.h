#ifndef PROGRAM_H
#define PROGRAM_H

#include "pinAssignment.h"
#include "drvLED.h"
#include "drvSleepCtl.h"
#include "drvButton.h"
#include "appTemperature.h"

#define DEBUG 1
#define SLEEP_TIMER_MS 5000

#if (DEBUG == 1)
#define DEBUG_MESSAGE_TIME_MS 1000
#endif

void program();
void sleepTask();
void mainLightTask();
void trunkLidTask();

#endif