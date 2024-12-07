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
uint32_t lastLcdRefreshMillis = millis();
uint32_t debug_timer = millis();

void program()
{
    sleepTask();
    mainLightTask();
    trunkLidTask();

    if (millis() - lastLcdRefreshMillis > 1 * 1000)
    {
        setTrunkLightState(trunkLidLight.isOn());
        setMainLightState(mainLight.isOn());
        lastLcdRefreshMillis = millis();
        appTemperature();
    }
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
        turnOffBacklight();
        Wire.end();
        digitalWrite(SLEEPLED_PIN, LOW);
        sleepCtrl.gotoSleep();
        Wire.begin();
        turnOnBacklight();
    }
}

void mainLightTask()
{
    mainSwitch.updateButton();
    mainLight.update();
#if (DEBUG == 1)
    if (millis() - debug_timer >= DEBUG_MESSAGE_TIME_MS)
    {
        Serial.print("Main Light State:");
        Serial.println(mainLight.getLedState());
    }
#endif
    if (mainSwitch.wasReleased())
    {
#if (DEBUG == 1)
        Serial.println("mainSwitch was pressed");
#endif
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
    trunkLidLight.update();
#if (DEBUG == 1)
    if (millis() - debug_timer >= DEBUG_MESSAGE_TIME_MS)
    {
        Serial.print("Trunk Light State:");
        Serial.println(trunkLidLight.getLedState());
    }
#endif
    if (trunkLidSwitch.wasReleased())
    {
#if (DEBUG == 1)
        Serial.println("mainSwitch was pressed");
#endif
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

#if (DEBUG == 1)
    if (millis() - debug_timer >= DEBUG_MESSAGE_TIME_MS)
        debug_timer = millis();
#endif
}
