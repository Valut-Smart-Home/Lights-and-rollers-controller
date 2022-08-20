#ifndef TIME_FAKE_H_
#define TIME_FAKE_H_

#include "../../src/hardware/time.h"

namespace lights_and_rollers::hardware {
  class TimeFake : public Time
  {
    public:
      void setTicks(const unsigned long&& ticks)
      {
        currentTicks = ticks;
      }
  };
}

#endif  // TIME_H_
