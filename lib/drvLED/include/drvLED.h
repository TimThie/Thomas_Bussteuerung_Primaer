#ifndef DRVLED_H
#define DRVLED_H
#include <Arduino.h>

#define DEFAULT_FADE_IN_TIME 1000
#define DEFAULT_FADE_OUT_TIME 1000

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
    } fadeConfig;

    DrvLED(uint8_t gpio);
    void setConfig(fadeConfig *config, fadeMode fadeInMode, uint32_t fadeInTime, fadeMode fadeOutMode, uint32_t fadeOutTime);
    void on();
    void off();
    void toggle();

private:
    enum ledState
    {
        LED_OFF = 0,
        LED_ON = 1
    };

    fadeConfig config;
    ledState ledState;

    uint8_t m_pin;

    void fadeIn();
    void fadeOut();
};
#endif