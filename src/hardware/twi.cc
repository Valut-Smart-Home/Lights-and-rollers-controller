#include "twi.h"

#include <avr/io.h>

namespace lights_and_rollers::hardware
{
  void Twi::Init()
  {
  }

  void Twi::Execute()
  {
  }

  bool Twi::is_ready()
  {
    return ready;
  }

  void Twi::ExecuteBuffer(const uint8_t&& count)
  {
    
  }
}
