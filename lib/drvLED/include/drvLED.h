#ifndef DRVLED_H
#define DRVLED_H
#include <Arduino.h>

#define DEFAULT_FADE_IN_TIME 1000
#define DEFAULT_FADE_OUT_TIME 1000

#define DEBOUNCE_TOGGLE_TIME_MS 500

#define MAX_BRIGHTNESS_LEVEL 255

class DrvLED
{
public:
    typedef enum fadeMode
    {
        noFading = 0,
        linear = 1

    } fadeMode;

    typedef struct fadeConfig
    {
        uint32_t fadeInTime;
        uint32_t fadeOutTime;
        fadeMode fadeInMode;
        fadeMode fadeOutMode;
        uint8_t maxBrightnessLevel;
    } fadeConfig;

    DrvLED(uint8_t gpio);
    void setConfig(fadeMode fadeInMode, uint32_t fadeInTime, fadeMode fadeOutMode, uint32_t fadeOutTime);
    void on();
    void off();
    void toggle();
    void setMaxBrightness(uint8_t maxBrightness);

private:
    enum ledState
    {
        LED_OFF = 0,
        LED_ON = 1,
        LED_RISING = 2,
        LED_FALLING = 3
    };

    fadeConfig config;
    ledState ledState;

    uint8_t m_pin;
    uint8_t brightness;
    uint32_t lastToggleMillis;
};
#endif