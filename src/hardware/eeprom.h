#ifndef EEPROM_H_
#define EEPROM_H_

#include <inttypes.h>

namespace lights_and_rollers::hardware {
  class Eeprom
  {
    public:
      static void SaveConfiguration();
      static void LoadConfiguration();
      static void SaveLights();
      static void LoadLights();
  };
}

#endif  // EEPROM_H_
