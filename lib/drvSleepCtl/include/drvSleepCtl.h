#ifndef DRVSLEEPCTL_H
#define DRVSLEEPCTL_H
#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

class DrvSleepCtrl
{
private:
    uint8_t wakePin;

    static DrvSleepCtrl *instance;
    static void sleepISR();
    uint32_t _sleepTimer;
    bool _isReadyToSleep;

public:
    DrvSleepCtrl(uint8_t wakeUpGPIO);
    ~DrvSleepCtrl();

    void gotoSleep();
    void setReadyForSleep(bool isReady);
    bool isReadyForSleep();
    uint32_t getSleepTimer();
    void resetSleepTimer();
};

#endif