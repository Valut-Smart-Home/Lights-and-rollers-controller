#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <inttypes.h>


namespace lights_and_rollers::base {
  class Configuration
  {  
    public:
      static const uint8_t kExpectedVersion = 1;

      uint8_t version = kExpectedVersion;
  };
  
  Configuration configuration = Configuration();
  uint16_t expectedLightsState[32] = { 0 };
}

#endif  // CONFIGURATION_H_