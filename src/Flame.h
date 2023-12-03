#include <Arduino.h>

class Flame
{
  public:
    void setup(int pin, int alpha = 20, int delay = 100);
    void flicker();
    void stop();

  private:
    int _pin;
    int _brightness = 0;  // soft start
    int _oldBrightness = 0;
    int _updateDelay;
    unsigned long _nextUpdate;
    int _alpha; // filter coefficient (0..100). Low means slow changes
};