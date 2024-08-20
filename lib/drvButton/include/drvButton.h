#ifndef DRVBUTTON_H
#define DRVBUTTON_H

#include <Arduino.h>

// Debounce time in milliseconds
#define DEBOUNCE_TIME 25

class DrvButton
{
public:
    DrvButton(uint8_t gpio, bool activeState = LOW);

    bool isPressed();
    bool wasClicked();
    bool wasClickedSec();
    bool wasClickedTime(uint32_t time);

private:
    uint8_t _pin;
    bool _activeState;
    bool _lastState;
    bool _isPressed;
    uint32_t _lastDebounceTime;
    uint32_t _pressedTime;

    // Internal method to handle debouncing
    void init();
    bool debounce();
};

#endif
