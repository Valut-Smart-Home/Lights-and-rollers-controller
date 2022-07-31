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
      void read(uint8_t id, uint8_t address, uint8_t count);
      void write(uint8_t id, uint8_t address, uint8_t count);
      uint8_t buffer[255];
  };
}

#endif  // I2C_H_
