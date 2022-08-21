#include "eeprom.h"

#include "../base/configuration.h"

#include <inttypes.h>
#include <avr/eeprom.h>

lights_and_rollers::base::Configuration ee_configuration EEMEM;
uint16_t ee_lights_state[32] EEMEM;

namespace lights_and_rollers::hardware {
    void Eeprom::SaveConfiguration() {
        eeprom_update_block(&ee_configuration, &lights_and_rollers::base::configuration, sizeof(lights_and_rollers::base::Configuration));
    }

    void Eeprom::LoadConfiguration() {
        if (eeprom_read_byte(&ee_configuration.version) == lights_and_rollers::base::Configuration::kExpectedVersion) {
            eeprom_read_block(&lights_and_rollers::base::configuration, &ee_configuration, sizeof(lights_and_rollers::base::Configuration));
        }
    }

    void Eeprom::SaveLights() {
        eeprom_update_block(&ee_lights_state, &lights_and_rollers::base::expectedLightsState, sizeof(ee_lights_state));
    }

    void Eeprom::LoadLights() {
        eeprom_read_block(&lights_and_rollers::base::expectedLightsState, &ee_lights_state, sizeof(ee_lights_state));
    }
}
