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
  };
}

#endif  // UART_H_
