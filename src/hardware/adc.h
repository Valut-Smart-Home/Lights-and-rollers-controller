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

      const uint8_t& last_readed() { return lastReaded; }
      uint16_t values[8] {0};

    protected:
      uint8_t lastReaded;

    private:
      uint8_t currentChannelIndex;
  };
}

#endif  // ADC_H_
