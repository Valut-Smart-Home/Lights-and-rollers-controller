#ifndef I2C_H_
#define I2C_H_

#include <inttypes.h>

#include "../base/module.h"

namespace lights_and_rollers::hardware {
  class Twi : public base::Module
  {
    public:
      Twi(): base::Module(base::Stage::kHardwareInteraction) { }

      void Init() override;
      void Execute() override;

      bool is_ready();
      bool is_ok();
      uint8_t buffer[255];
      void ExecuteBuffer(const uint8_t&& count);

    protected:
      bool ok_;
      uint8_t state_;

    private:
      uint8_t count_;
      uint8_t bufferIndex_;
  };
}

#endif  // I2C_H_
