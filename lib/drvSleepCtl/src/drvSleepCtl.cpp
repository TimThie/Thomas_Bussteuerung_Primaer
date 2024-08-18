#include "drvSleepCtl.h"
DrvSleepCtrl *DrvSleepCtrl::instance = nullptr;
DrvSleepCtrl::DrvSleepCtrl(uint8_t wakeUpGPIO)
{
    this->wakePin = wakeUpGPIO;
    instance = this;
}

DrvSleepCtrl::~DrvSleepCtrl()
{
}

void DrvSleepCtrl::gotoSleep()
{
    // Disable the ADC (Analog to digital converter, pins A0 [14] to A5 [19])
    static byte prevADCSRA = ADCSRA;
    ADCSRA = 0;

    /* Set the type of sleep mode we want. Can be one of (in order of power saving):

        SLEEP_MODE_IDLE (Timer 0 will wake up every millisecond to keep millis running)
        SLEEP_MODE_ADC
        SLEEP_MODE_PWR_SAVE (TIMER 2 keeps running)
        SLEEP_MODE_EXT_STANDBY
        SLEEP_MODE_STANDBY (Oscillator keeps running, makes for faster wake-up)
        SLEEP_MODE_PWR_DOWN (Deep sleep)
    */
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    // Turn of Brown Out Detection (low voltage)
    // Thanks to Nick Gammon for how to do this (temporarily) in software rather than
    // permanently using an avrdude command line.
    //
    // Note: Microchip state: BODS and BODSE only available for picoPower devices ATmega48PA/88PA/168PA/328P
    //
    // BODS must be set to one and BODSE must be set to zero within four clock cycles. This sets
    // the MCU Control Register (MCUCR)
    MCUCR = bit(BODS) | bit(BODSE);

    // The BODS bit is automatically cleared after three clock cycles so we better get on with it
    MCUCR = bit(BODS);

    // Ensure we can wake up again by first disabling interupts (temporarily) so
    // the wakeISR does not run before we are asleep and then prevent interrupts,
    // and then defining the ISR (Interrupt Service Routine) to run when poked awake
    noInterrupts();

    attachInterrupt(digitalPinToInterrupt(this->wakePin), sleepISR, LOW);

    // Send a message just to show we are about to sleep
    // Serial.println("Good night!");
    Serial.flush();

    // Allow interrupts now
    interrupts();

    // And enter sleep mode as set above
    sleep_cpu();

    // --------------------------------------------------------
    // µController is now asleep until woken up by an interrupt
    // --------------------------------------------------------

    // Wakes up at this point when wakePin is brought LOW - interrupt routine is run first
    // Serial.println("I'm awake!");

    // Re-enable ADC if it was previously running
    ADCSRA = prevADCSRA;
}

// When wakePin is brought LOW this interrupt is triggered FIRST (even in PWR_DOWN sleep)
// void DrvSleepCtrl::sleepISR()
// {
//     // Prevent sleep mode, so we don't enter it again, except deliberately, by code
//     sleep_disable();

//     // Detach the interrupt that brought us out of sleep
//     for (size_t i = 0; i < sizeof(this->wakePins); i++)
//     {
//         detachInterrupt(digitalPinToInterrupt(this->wakePins[i]));
//     }

//     // Now we continue running the main Loop() just after we went to sleep
// }
void DrvSleepCtrl::sleepISR()
{
    Serial.println("Wake Up");
    // Prevent sleep mode, so we don't enter it again, except deliberately, by code
    sleep_disable();
    // Detach the interrupt that brought us out of sleep
    detachInterrupt(digitalPinToInterrupt(instance->wakePin));

    // Now we continue running the main Loop() just after we went to sleep
}