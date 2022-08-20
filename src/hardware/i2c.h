#ifndef I2C_H_
#define I2C_H_

#include <inttypes.h>

#include "../base/module.h"

namespace lights_and_rollers::hardware {
  class I2c : public base::Module
  {
    public:
      I2c(): base::Module(base::Stage::kHardwareInteraction) { }

      void Init() override;
      void Execute() override;

      bool is_ready();
      uint8_t buffer[255];
      void ExecuteBuffer(const uint8_t&& count);
    protected:
      bool ready;
  };
}

#endif  // I2C_H_
