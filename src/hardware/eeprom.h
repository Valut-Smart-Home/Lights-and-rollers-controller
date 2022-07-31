#ifndef EEPROM_H_
#define EEPROM_H_

#include <inttypes.h>

namespace lights_and_rollers::hardware {
  class Eeprom
  {
    public:
      void Init();
      void Save();
      void Load();

      bool is_ready();
  };
}

#endif  // EEPROM_H_
