#include "base/setup.h"

int main()
{
  auto setup = lights_and_rollers::base::Setup();
  setup.CreateObjects();
  // setup.ReadConfiguration();
  setup.InitModules();
  // setup.SetupPowerOut();
    
  while (true)
  {
    setup.ExecuteModules();
  }
}


// No stage
    // Power out
    // Settings
    // eeprom
// Stage 0 - Hardware interaction
    // twi
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
