#include "base/setup.h"

namespace lights_and_rollers {
  int main()
  {
    auto setup = base::Setup();
    auto modules = setup.CreateObjects();
    
    setup.ReadConfiguration();
    
    for (auto mod: setup.modules)
      mod->Init();
    
    setup.SetupPowerOut();
      
    while (true)
    {
      for (auto mod: setup.modules)
        mod->Execute();
    }
  }
}


// No stage
    // Power out
    // Settings
    // eeprom
// Stage 0 - Hardware interaction
    // i2c
    // uart
    // AC
    // TIME
// Stage 1 - Reading inputs
    // BTN_IN
    // ROLLERS_IN
    // COMMUNICATION_IN
// Stage 2 - Interpretation of inputs
    // BTN_FNC
    // ROLLERS_FNC
// Stage 3 - Reaction (BI)
    // ROLLERS_CTRL
    // LIGHTS_CTRL
// Stage 4 - Prepare outputs
    // LIGHTS_OUT
    // ROLLERS_OUT
// Stage 5 - Configuration changes and comunnication
    // PROTOCOL_MANAGER
