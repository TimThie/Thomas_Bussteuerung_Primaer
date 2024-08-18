#include "drvLED.h"

DrvLED::DrvLED(uint8_t gpio)
{
    this->m_pin = gpio;
    pinMode(this->m_pin, OUTPUT);
    setConfig(linear, DEFAULT_FADE_IN_TIME, noFading, DEFAULT_FADE_OUT_TIME);
}

void DrvLED::setConfig(fadeMode fadeInMode, uint32_t fadeInTime, fadeMode fadeOutMode, uint32_t fadeOutTime)
{
    this->config.fadeInMode = fadeInMode;
    this->config.fadeInTime = fadeInTime;
    this->config.fadeOutMode = fadeOutMode;
    this->config.fadeOutTime = fadeOutTime;
    this->config.maxBrightnessLevel = MAX_BRIGHTNESS_LEVEL;
}

void DrvLED::on()
{
    uint32_t fadeTimer = millis();
    uint8_t ledBrightness = 0;
    switch (this->config.fadeInMode)
    {
    case noFading:
        digitalWrite(this->m_pin, HIGH);
        break;
    case linear:
        this->ledState = LED_RISING;

        while (ledBrightness < this->config.maxBrightnessLevel)
        {
            if (millis() - fadeTimer >= fadeTimer + this->config.fadeInTime / MAX_BRIGHTNESS_LEVEL) // Hier funzt was noch nicht !!!
            {
                fadeTimer = millis();
                ledBrightness++;
                analogWrite(this->m_pin, ledBrightness);
            }
        }
        break;
    default:
        break;
    }

    this->ledState = LED_ON;
}

void DrvLED::off()
{
    switch (this->config.fadeOutMode)
    {
    case noFading:
        digitalWrite(this->m_pin, LOW);
        break;
    case linear:
        /* code */
        break;

    default:
        break;
    }

    this->ledState = LED_OFF;
}

void DrvLED::toggle()
{
    if (!(this->ledState > LED_ON))
    {
        if (this->ledState == LED_ON)
        {
            off();
        }
        else
        {
            on();
        }
    }
}
