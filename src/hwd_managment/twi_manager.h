#ifndef TWI_MANAGER_H_
#define TWI_MANAGER_H_

#include <inttypes.h>

#include "../base/module.h"
#include "../base/twi_user.h"
#include "../hardware/twi.h"

namespace lights_and_rollers::hwd_management {
  class TwiManager : public base::Module
  {
    public:
      TwiManager(hardware::Twi* twi): base::Module(base::Stage::kHardwareMangement), twi_(twi) { }

      void Init() override;
      void Execute() override;

      void RegisterUser(base::TwiUser* user);
      void NextUser();

      void Read(uint8_t id, uint8_t count);
      void Write(uint8_t id, uint8_t count);
      uint8_t* GetBufferStart();

    private:
      base::TwiUser* firstUser_{nullptr};
      base::TwiUser* currentUser_{nullptr};
      hardware::Twi* twi_;
  };
}

#endif  // TWI_MANAGER_H_