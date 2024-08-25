#include "program.h"

/*Sleep Taks*/
DrvSleepCtrl sleepCtrl(WAKEUP_PIN);

/*Main Light Task*/
DrvButton mainSwitch(MAINLIGHTBUTTON_PIN, LOW);
DrvLED mainLight(MAINLIGHT_PIN);

/*Main Light Task*/
DrvButton trunkLidSwitch(TRUNK_LID_LIGHT_BUTTON_PIN, LOW);
DrvLED trunkLidLight(TRUNK_LID_LIGHT_PIN);

uint32_t currentMainSwitchMillis;

void program()
{
    sleepTask();
    mainLightTask();
    trunkLidTask();
}

void sleepTask()
{
    digitalWrite(SLEEPLED_PIN, HIGH);
    bool sleepCondition = 0;
    sleepCondition |= !mainLight.isOff();
    sleepCondition |= !trunkLidLight.isOff();
    if (sleepCondition == 0)
    {
        sleepCtrl.setReadyForSleep(true);
    }
    else
    {
        sleepCtrl.setReadyForSleep(false);
    }

    if (sleepCtrl.isReadyForSleep() && millis() - sleepCtrl.getSleepTimer() > SLEEP_TIMER_MS)
    {
        digitalWrite(SLEEPLED_PIN, LOW);
        sleepCtrl.gotoSleep();
    }
}

void mainLightTask()
{
    mainSwitch.updateButton();
    if (mainSwitch.wasReleased())
    {
        if (mainSwitch.wasPressedLong())
        {
            mainLight.setMaxBrightness(5);
            mainLight.toggle();
        }
        else
        {
            mainLight.setMaxBrightness(255);
            mainLight.toggle();
        }
    }
}

void trunkLidTask()
{
    trunkLidSwitch.updateButton();
    if (trunkLidSwitch.wasReleased())
    {
        if (trunkLidSwitch.wasPressedLong())
        {
            trunkLidLight.setMaxBrightness(5);
            trunkLidLight.toggle();
        }
        else
        {
            trunkLidLight.setMaxBrightness(255);
            trunkLidLight.toggle();
        }
    }
}
