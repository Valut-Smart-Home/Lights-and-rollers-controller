#include "time.h"

#include <avr/io.h>

namespace lights_and_rollers::hardware
{
  void Time::Init()
  {
    TCCR0A =
      (0 << COM0A1) | (0 << COM0A0) |
      (0 << COM0B1) | (0 << COM0B0) |
      (0 << WGM01) | (0 << WGM00);
    TCCR0B =
      (0 << FOC0A) | (0 << FOC0B) |
      (0 << WGM02) |
      (1 << CS02) | (0 << CS01) | (1 << CS00); // 1024 prescaller
  }

  void Time::Execute()
  {
    static uint8_t lastValue;

    uint8_t curValue = TCNT0;
    currentTicks += curValue - lastValue;
    lastValue = curValue;
  }

  unsigned long Time::msToTicks(const unsigned long&& ms)
  {
    return ms * F_CPU / 1024000U;
  }
}
