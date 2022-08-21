#include "adc.h"

#include <avr/io.h>

const uint8_t channels[]{ 0, 1, 2, 3, 6, 7 };

inline void adc_set_channel(const uint8_t& channel) {
   ADMUX = channel | _BV(REFS0);
}

inline void adc_start() {
    ADCSRA |= _BV(ADIF);
    ADCSRA |= _BV(ADSC);
}

bool adc_is_ready() {
  return ADCSRA & _BV(ADIF);
} 

namespace lights_and_rollers::hardware {
  void Adc::Init() {
    ADCSRA = 
      _BV(ADEN) |
      _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    DIDR0 = _BV(ADC3D) | _BV(ADC2D) | _BV(ADC1D) | _BV(ADC0D);

    adc_set_channel(channels[0]);
    adc_start();
  }

  void Adc::Execute() {
    if (adc_is_ready()) {
      values[currentChannelIndex] = ADC;
      lastReaded = currentChannelIndex;
      ++currentChannelIndex;
      if (currentChannelIndex >= sizeof(channels)) {
        currentChannelIndex = 0;
      }

      adc_set_channel(channels[currentChannelIndex]);
      adc_start();
    }
  }

  const uint8_t& Adc::last_readed() {
    return lastReaded;
  }
}