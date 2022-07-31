#ifndef TIME_H_
#define TIME_H_

#include <inttypes.h>

#include "../base/module.h"

namespace lights_and_rollers::hardware {
  class Time : public base::Module
  {
    public:
      Time(): base::Module(base::Stage::kHardwareInteraction)
      { }

      void Init() override;
      void Execute() override;

      unsigned long millis();
  };
}

#endif  // TIME_H_
