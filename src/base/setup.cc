#include "setup.h"
#include "../hardware/eeprom.h"
#include "../hardware/adc.h"
#include "../hardware/twi.h"
#include "../hardware/time.h"
#include "../hardware/uart.h"
#include "../hwd_managment/twi_manager.h"
// #include "../input/button.h"
// #include "../input/roller.h"

lights_and_rollers::hardware::Eeprom eeprom = {};

namespace lights_and_rollers::base {
  void Setup::CreateObjects()
  {
    #define CREATE_MODULE(T, name, ...) T name{__VA_ARGS__}; modules[moduleCounter++] = &name;

    CREATE_MODULE(hardware::Time, time)
    CREATE_MODULE(hardware::Adc, adc)
    CREATE_MODULE(hardware::Twi, twi)
    CREATE_MODULE(hardware::Uart, uart)

    CREATE_MODULE(hwd_management::TwiManager, twiManager, &twi);

    // CREATE_MODULE(input::Button, btn_input, &time, &twiManager)

    #undef CREATE_MODULE
  }

  void Setup::ReadConfiguration() {

  }

  void Setup::InitModules() {
    for (unsigned int i = 0; i<N; ++i) {
      modules[i]->Init();
    }
  }

  void Setup::SetupPowerOut() {

  }

  void Setup::ExecuteModules() {
    for (unsigned int i = 0; i < N; ++i) {
      modules[i]->Execute();
    }
  }
}

