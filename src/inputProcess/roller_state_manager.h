#ifndef ROLLER_H_
#define ROLLER_H_

#include <inttypes.h>

#include "../base/module.h"

namespace lights_and_rollers::input {
  class Roller : public base::Module
  {
    public:
      Roller(); // : base::Module(base::Stage::kInterpretateInputs)

      void Init() override;
      void Execute() override;
  };
}

#endif  // ROLLER_H_
