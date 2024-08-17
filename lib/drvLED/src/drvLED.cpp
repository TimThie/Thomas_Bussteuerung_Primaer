#include "drvLED.h"

DrvLED::DrvLED(uint8_t gpio)
{
    this->m_pin = gpio;
    pinMode(this->m_pin, OUTPUT);
    setConfig(&this->config, noFading, DEFAULT_FADE_IN_TIME, noFading, DEFAULT_FADE_OUT_TIME);
}

void DrvLED::setConfig(fadeConfig *config, fadeMode fadeInMode, uint32_t fadeInTime, fadeMode fadeOutMode, uint32_t fadeOutTime)
{
    config->fadeInMode = fadeInMode;
    config->fadeInTime = fadeInTime;
    config->fadeOutMode = fadeOutMode;
    config->fadeOutTime = fadeOutTime;
}

void DrvLED::on()
{
    switch (this->config.fadeInMode)
    {
    case linear:
        /* code */
        break;

    default:
        digitalWrite(this->m_pin, HIGH);
        break;
    }

    this->ledState = LED_ON;
}

void DrvLED::off()
{
    switch (this->config.fadeOutMode)
    {
    case linear:
        /* code */
        break;

    default:
        digitalWrite(this->m_pin, LOW);
        break;
    }

    this->ledState = LED_OFF;
}

void DrvLED::toggle()
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
