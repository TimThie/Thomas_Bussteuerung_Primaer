#ifndef DRVSLEEPCTL_H
#define DRVSLEEPCTL_H
#include <Arduino.h>
#include <avr/sleep.h>

class DrvSleepCtrl
{
private:
    uint8_t wakePin;

    static DrvSleepCtrl *instance;
    static void sleepISR();

public:
    DrvSleepCtrl(uint8_t wakeUpGPIO);
    ~DrvSleepCtrl();

    void gotoSleep();
};

#endif