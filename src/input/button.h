#ifndef BUTTON_H_
#define BUTTON_H_

#include <inttypes.h>

#include "../base/module.h"
#include "../base/i2c_user.h"
#include "../hardware/time.h"
#include "../hwd_managment/i2c_manager.h"

namespace lights_and_rollers::input {
  class Button : public base::Module, public base::I2cUser
  {
    public:
      Button(hardware::Time* time, hwd_management::I2cManager* i2c) : base::Module(base::Stage::kInterpretateInputs), time_(time), i2c_(i2c) { }

      void Init() override;
      void Execute() override;
    
    private:
      const hardware::Time* time_;
      const hwd_management::I2cManager* i2c_;
  };
}

#endif  // BUTTON_H_
