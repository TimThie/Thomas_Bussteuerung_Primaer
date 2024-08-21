#include "program.h"

/*Sleep Taks*/
DrvSleepCtrl sleepCtrl(WAKEUP_PIN);

/*Main Light Task*/
DrvButton mainSwitch(MAINLIGHTBUTTON_PIN, LOW);
DrvLED mainLight(MAINLIGHT_PIN);

/*Main Light Task*/
DrvButton trunkLidSwitch(TRUNK_LID_LIGHT_BUTTON_PIN, LOW);
DrvLED trunkLidLight(TRUNK_LID_LIGHT_PIN);

void program()
{
    sleepTask();
    mainLightTask();
    trunkLidTask();
}

void sleepTask()
{
    digitalWrite(LED_BUILTIN, HIGH);
    if (digitalRead(WAKEUP_PIN) == LOW)
    {
        sleepCtrl.resetSleepTimer();
    }

    if (millis() - sleepCtrl.getSleepTimer() > SLEEP_TIMER_MS)
    {
        digitalWrite(LED_BUILTIN, LOW);
        sleepCtrl.gotoSleep();
        sleepCtrl.resetSleepTimer();
    }
}

void mainLightTask()
{
    if (mainSwitch.wasClicked())
    {
        mainLight.setMaxBrightness(255);
        mainLight.toggle();
    }
    else if (mainSwitch.wasClickedSec())
    {
        mainLight.setMaxBrightness(50);
        mainLight.toggle();
    }
}

void trunkLidTask()
{
}
