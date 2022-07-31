#ifndef ADC_H_
#define ADC_H_

#include <inttypes.h>

#include "../base/module.h"

namespace lights_and_rollers::hardware {
  class Adc : public base::Module
  {
    public:
      Adc(): base::Module(base::Stage::kHardwareInteraction)
      { }

      void Init() override;
      void Execute() override;

      bool is_new_reading();
      int last_readed();
      uint16_t values[8];
  };
}

#endif  // ADC_H_
