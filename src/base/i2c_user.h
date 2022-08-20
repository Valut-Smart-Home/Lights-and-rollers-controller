#ifndef I2C_USER_H_
#define I2C_USER_H_

namespace lights_and_rollers::base {
  class I2cUser
  {
    public:
      I2cUser* NextI2cUser = nullptr;
      
      virtual void I2cOnReady();
  };
}

#endif  // I2C_USER_H_