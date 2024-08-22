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

void DrvLED::on()
{
    bool err = false;
    uint32_t fadeTimer = millis();
    switch (this->config.fadeInMode)
    {
    case noFading:
        analogWrite(this->m_pin, this->config.maxBrightnessLevel);
        break;
    case linear:
        this->ledState = LED_RISING;

        while (this->brightness < this->config.maxBrightnessLevel)
        {
            /*            Serial.print(millis());
                        Serial.print(" - ");
                        Serial.print(fadeTimer);
                        Serial.print(" >= ");
                        Serial.print(fadeTimer);
                        Serial.print(" + ");
                        Serial.print(this->config.fadeInTime);
                        Serial.print(" / ");
                        Serial.print(MAX_BRIGHTNESS_LEVEL);
                        Serial.print(" * ");
                        Serial.print(ledBrightness + 1);
                        Serial.print(" -> ");
                        Serial.println((uint32_t)(this->config.fadeInTime / MAX_BRIGHTNESS_LEVEL * (ledBrightness + 1)));
                        */
            if (millis() - fadeTimer >= (uint32_t)(this->config.fadeInTime / MAX_BRIGHTNESS_LEVEL * (this->brightness + 1)))
            {
                this->brightness++;
                analogWrite(this->m_pin, this->brightness);
            }
        }
        break;
    default:
        err = true;
        break;
    }

    if (!err)
    {
        this->ledState = LED_ON;
    }
}

void DrvLED::off()
{
    bool err = false;
    uint8_t fadeOutCounter = 1;
    uint32_t fadeTimer = millis();
    switch (this->config.fadeOutMode)
    {
    case noFading:
        digitalWrite(this->m_pin, LOW);
        break;
    case linear:
        this->ledState = LED_FALLING;

        while (this->brightness > LOW)
        {
            /*            Serial.print(millis());
                        Serial.print(" - ");
                        Serial.print(fadeTimer);
                        Serial.print(" >= ");
                        Serial.print(fadeTimer);
                        Serial.print(" + ");
                        Serial.print(this->config.fadeInTime);
                        Serial.print(" / ");
                        Serial.print(MAX_BRIGHTNESS_LEVEL);
                        Serial.print(" * ");
                        Serial.print(fadeOutCounter + 1);
                        Serial.print(" -> ");
                        Serial.println((uint32_t)(this->config.fadeInTime / MAX_BRIGHTNESS_LEVEL * (fadeOutCounter + 1)));
                        */
            if (millis() - fadeTimer >= (uint32_t)(this->config.fadeOutTime / MAX_BRIGHTNESS_LEVEL * (fadeOutCounter + 1))) // Hier funzt was noch nicht !!!
            {
                this->brightness--;
                fadeOutCounter++;
                analogWrite(this->m_pin, this->brightness);
            }
        }
        break;

    default:
        err = true;
        break;
    }

    if (!err)
    {
        this->ledState = LED_OFF;
    }
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
        this->lastToggleMillis = millis();
    }
}

void DrvLED::setMaxBrightness(uint8_t maxBrightness)
{
    this->config.maxBrightnessLevel = maxBrightness;
}

bool DrvLED::isOn()
{
    if (this->ledState == LED_ON)
    {
        return true;
    }
    return false;
}
