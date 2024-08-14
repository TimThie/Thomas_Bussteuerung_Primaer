#include "drvSleepCtl.h"

void gotoSleep(uint32_t time);
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); /*ok*/
    sleep_enable();

    /*ADC Deaktivieren*/
    ADCSRA &= ~(1 << ADEN);
    sleep_mode();
    sleep_disable();
}

void setupSleepTask()
{
    /*Init*/
    pinMode(LIGHTSWITCH_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(LIGHTSWITCH_PIN), wakeUp, RISING);
}

void setupWatchdogTimer_SLEEP()
{
    MCUSR &= ~(1 << WDRF);              // Clear the reset flag
    WDTCSR |= (1 << WDCE) | (1 << WDE); // Enable WDT change
    WDTCSR = (1 << WDP3) | (1 << WDP0); // Set WDT for 8s timeout
    WDTCSR |= (1 << WDIE);              // Enable WDT interrupt
}

void wakeUp()
{
    pinInterrupt = true; // Set flag when pin 5 is pulled low
}