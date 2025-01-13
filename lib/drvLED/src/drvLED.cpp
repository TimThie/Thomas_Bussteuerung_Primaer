#include "drvLED.h"

DrvLED::DrvLED(uint8_t gpio)
{
    this->m_pin = gpio;
    pinMode(this->m_pin, OUTPUT);
    setConfig(linear, DEFAULT_FADE_IN_TIME, linear, DEFAULT_FADE_OUT_TIME);
}

void DrvLED::setConfig(fadeMode fadeInMode, uint32_t fadeInTime, fadeMode fadeOutMode, uint32_t fadeOutTime)
{
    this->config.fadeInMode = fadeInMode;
    this->config.fadeInTime = fadeInTime;
    this->config.fadeOutMode = fadeOutMode;
    this->config.fadeOutTime = fadeOutTime;
    this->config.maxBrightnessLevel = MAX_BRIGHTNESS_LEVEL;
}

void DrvLED::turnOn()
{
    // Switch-case to handle different fade-in modes
    switch (this->config.fadeInMode)
    {
    case noFading:
        // No fading, set LED to max brightness immediately
        analogWrite(this->m_pin, this->config.maxBrightnessLevel);
        this->ledState = LED_ON;
        break;
    case linear:
        // Linear fading mode
        if (this->brightness < this->config.maxBrightnessLevel)
        {
            this->ledState = LED_RISING;
            // Check if it's time to increase brightness
            if (millis() - this->lastToggleMillis >= (uint32_t)(this->config.fadeInTime / MAX_BRIGHTNESS_LEVEL * (this->brightness + 1)))
            {
                this->brightness++;
                analogWrite(this->m_pin, this->brightness);
            }
        }
        else
        {
            this->ledState = LED_ON;
        }
        break;
    default:
// Handle unexpected fadeInMode
#if DEBUG == 1
        Serial.println("Error: Unknown fadeInMode");
#endif
        break;
    }
}

void DrvLED::turnOff()
{
    // Switch-case to handle different fade-out modes
    switch (this->config.fadeOutMode)
    {
    case noFading:
        // No fading, turn off LED immediately
        analogWrite(this->m_pin, LOW);
        this->ledState = LED_OFF;
        break;
    case linear:
        // Linear fading mode
        if (this->brightness > 0)
        {
            this->ledState = LED_FALLING;
            // Check if it's time to decrease brightness
            if (millis() - this->lastToggleMillis >= (uint32_t)(this->config.fadeOutTime / 2 / MAX_BRIGHTNESS_LEVEL))
            {
                this->brightness--;
                analogWrite(this->m_pin, this->brightness);
                this->lastToggleMillis = millis(); // Reset the last toggle time
            }
        }
        else
        {
            analogWrite(this->m_pin, LOW);
            this->ledState = LED_OFF;
        }
        break;
    default:
// Handle unexpected fadeOutMode
#if DEBUG == 1
        Serial.println("Error: Unknown fadeOutMode");
#endif
        break;
    }
}

void DrvLED::toggle()
{

    if (this->ledState == LED_ON || this->ledState == LED_RISING)
    {
        turnOff();
    }
    else
    {
        turnOn();
    }
    this->lastToggleMillis = millis();
}

void DrvLED::setMaxBrightness(uint8_t maxBrightness)
{
    this->config.maxBrightnessLevel = maxBrightness;
}

bool DrvLED::isOn()
{
    if (this->ledState > LED_OFF)
    {
        return true;
    }
    return false;
}

bool DrvLED::isOff()
{
    if (this->ledState == LED_OFF)
    {
        return true;
    }
    return false;
}

void DrvLED::update()
{
    switch (this->ledState)
    {
    case LED_FALLING:
        turnOff();
        break;

    case LED_RISING:
        turnOn();
        break;

    default:
        break;
    }
}

uint8_t DrvLED::getLedState()
{
    return this->ledState;
}
