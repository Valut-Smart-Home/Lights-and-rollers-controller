#ifndef I2C_USER_H_
#define I2C_USER_H_

namespace lights_and_rollers::base {
  class TwiUser
  {
    public:
      TwiUser* NextTwiUser = nullptr;
      
      virtual void TwiOnReady();
  };
}

#endif  // I2C_USER_H_