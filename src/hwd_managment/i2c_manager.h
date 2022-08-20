#ifndef I2C_MANAGER_H_
#define I2C_MANAGER_H_

#include <inttypes.h>

#include "../base/module.h"
#include "../base/i2c_user.h"
#include "../hardware/i2c.h"

namespace lights_and_rollers::hwd_management {
  class I2cManager : public base::Module
  {
    public:
      I2cManager(hardware::I2c* i2c): base::Module(base::Stage::kHardwareMangement), i2c_(i2c) { }

      void Execute() override;

      void RegisterUser(base::I2cUser* user);
      void NextUser();

      void Read(uint8_t id, uint8_t address, uint8_t count);
      void Write(uint8_t id, uint8_t address, uint8_t count);

    private:
      base::I2cUser* firstUser_;
      base::I2cUser* currentUser_;
      const hardware::I2c* i2c_;
  };
}

#endif  // I2C_MANAGER_H_