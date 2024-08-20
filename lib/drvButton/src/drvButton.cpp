#include "drvButton.h"

DrvButton::DrvButton(uint8_t gpio, bool activeState)
    : _pin(gpio), _activeState(activeState), _lastState(!activeState),
      _isPressed(false), _lastDebounceTime(0), _pressedTime(0) { this->init(); }

void DrvButton::init()
{
    pinMode(_pin, INPUT);
}

bool DrvButton::debounce()
{
    bool currentState = digitalRead(_pin) == _activeState;
    if (currentState != _lastState)
    {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > DEBOUNCE_TIME)
    {
        if (currentState != _isPressed)
        {
            _isPressed = currentState;
            if (_isPressed)
            {
                _pressedTime = millis();
            }
        }
    }

    _lastState = currentState;
    return _isPressed;
}

bool DrvButton::isPressed()
{
    return debounce();
}

bool DrvButton::wasClicked()
{
    if (!debounce() && _pressedTime != 0)
    {
        uint32_t duration = millis() - _pressedTime;
        _pressedTime = 0;
        return (duration > DEBOUNCE_TIME && duration < 1000);
    }
    return false;
}

bool DrvButton::wasClickedSec()
{
    if (!debounce() && _pressedTime != 0)
    {
        uint32_t duration = millis() - _pressedTime;
        _pressedTime = 0;
        return (duration >= 1000);
    }
    return false;
}

bool DrvButton::wasClickedTime(uint32_t time)
{
    if (!debounce() && _pressedTime != 0)
    {
        uint32_t duration = millis() - _pressedTime;
        _pressedTime = 0;
        return (duration >= time);
    }
    return false;
}
