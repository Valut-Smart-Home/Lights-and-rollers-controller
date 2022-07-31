#ifndef UART_H_
#define UART_H_

#include <inttypes.h>

#include "../base/module.h"

namespace lights_and_rollers::hardware {
  class Uart : public base::Module
  {
    public:
      Uart(): base::Module(base::Stage::kHardwareInteraction) { }

      void Init() override;
      void Execute() override;

      void is_send_ready();
      void to_send(const uint8_t &byte);

      bool is_new_byte();
      const uint8_t& last_byte_readed();
  };
}

#endif  // UART_H_
