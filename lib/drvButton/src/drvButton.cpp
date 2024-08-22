#include "drvButton.h"

DrvButton::DrvButton(uint8_t gpio, bool activeState)
{
    this->_pin = gpio;
    this->_currentStateMillis = millis();
    this->_activeState = LOW;
    this->_button = Bounce2::Button();

    if (this->_activeState == LOW)
    {
        this->_button.attach(this->_pin, INPUT_PULLUP);
    }
    else
    {
        this->_button.attach(this->_pin, INPUT);
    }
    this->_button.interval(DEBOUNCE_TIME);
    this->_button.setPressedState(LOW);
}

bool DrvButton::isPressed()
{
    return this->_button.isPressed();
}

bool DrvButton::wasPressed()
{
    return this->_button.pressed();
}

bool DrvButton::wasReleased()
{
    return this->_button.released();
}

bool DrvButton::wasPressedLong()
{
    if (millis() - this->_currentStateMillis > PRESS_LONG_DURATION_MS)
    {
        return true;
    }
    return false;
}

void DrvButton::updateButton()
{
    if (!this->_button.isPressed())
    {
        _currentStateMillis = millis();
    }
    this->_button.update();
}
