#include "Flame.h"

void Flame::setup(int pin, int alpha, int delay)
{
  constrain(alpha, 0, 100);
  _pin = pin;
  _alpha = alpha;
  _updateDelay = delay;
  // random first upate to prevent multiple flames looking synchronous
  _nextUpdate = millis() + random(_updateDelay);
}

void Flame::flicker()
{
  if (millis() >= _nextUpdate)
  {
    _nextUpdate += _updateDelay;
    _brightness = random(0, 255);
    // low pass filter the brightness changes
    _brightness = (_alpha * _brightness + (100 - _alpha) * _oldBrightness) / 100;
    _oldBrightness = _brightness;
    analogWrite(_pin, _brightness);
  }
}

void Flame::stop()
{
  analogWrite(_pin, LOW);
}