#ifndef BUTTON_H_
#define BUTTON_H_

#include <inttypes.h>

#include "../base/module.h"
#include "../hardware/time.h"
#include "../hardware/i2c.h"

namespace lights_and_rollers::input {
  class Button : public base::Module
  {
    public:
      Button(hardware::Time time, hardware::I2c i2c); // : base::Module(base::Stage::kInterpretateInputs)

      void Init() override;
      void Execute() override;
    
    private:
      hardware::Time time;
      hardware::I2c i2c;
  };
}

#endif  // BUTTON_H_
