#ifndef DRVBUTTON_H
#define DRVBUTTON_H

#include <Arduino.h>
#include <Bounce2.h>

// Debounce time in milliseconds
#define DEBOUNCE_TIME 20
#define PRESS_LONG_DURATION_MS 1000

class DrvButton
{
public:
    DrvButton(uint8_t gpio, bool activeState = LOW);

    void updateButton();
    bool isPressed();
    bool wasPressed();
    bool wasReleased();
    bool wasPressedLong();
    Bounce2::Button
    getButtonObject();

private:
    Bounce2::Button _button;
    uint8_t _pin;
    bool _activeState;
    uint32_t _currentStateMillis;

    // Internal method to handle debouncing
    void init();
};

#endif
