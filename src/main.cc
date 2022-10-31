#include "base/setup.h"
#include "hardware/eeprom.h"

// TIMER0 used by Time module
// PC4, PC5 used by Twi module
// PC1, PC2, PC3, ADC6, ADC7 used by ADC
// PD0, PD1, PD2 used by Uart module

int main()
{
  auto setup = lights_and_rollers::base::Setup();
  setup.CreateObjects();
  lights_and_rollers::hardware::Eeprom::LoadConfiguration();
  lights_and_rollers::hardware::Eeprom::LoadLights();
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
