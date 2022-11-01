#ifndef TWI_H_
#define TWI_H_

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
      virtual void ExecuteBuffer(const uint8_t&& count);

    protected:
      bool ok_{true};
      uint8_t state_{0U};

    private:
      uint8_t count_;
      uint8_t bufferIndex_;
  };
}

#endif  // TWI_H_
