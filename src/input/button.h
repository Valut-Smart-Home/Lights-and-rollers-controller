#ifndef BUTTON_H_
#define BUTTON_H_

#include <inttypes.h>

#include "../base/module.h"
#include "../base/twi_user.h"
#include "../hardware/time.h"
#include "../hwd_managment/twi_manager.h"

namespace lights_and_rollers::input {
  class Button : public base::Module, public base::TwiUser
  {
    public:
      Button(hardware::Time* time, hwd_management::TwiManager* twi) : base::Module(base::Stage::kInterpretateInputs), time_(time), twi_(twi) { }

      void Init() override;
      void Execute() override;
    
    private:
      const hardware::Time* time_;
      const hwd_management::TwiManager* twi_;
  };
}

#endif  // BUTTON_H_
