#ifndef TWI_USER_H_
#define TWI_USER_H_

namespace lights_and_rollers::base {
  class TwiUser
  {
    public:
      TwiUser* NextTwiUser = nullptr;
      
      virtual void TwiOnReady() = 0;
  };
}

#endif  // TWI_USER_H_