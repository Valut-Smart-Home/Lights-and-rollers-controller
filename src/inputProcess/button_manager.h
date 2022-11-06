#ifndef BUTTON_MANAGER_H_
#define BUTTON_MANAGER_H_

#include "../base/module.h"
#include "../hardware/time.h"
#include "../inputRead/external_io_reader.h"

namespace lights_and_rollers::inputProcess {
  class ButtonManager : public base::Module
  {
    public:
      ButtonManager(hardware::Time* time, inputRead::ExternalIoReader* reader) : base::Module(base::Stage::kProcessInputs), time_(time), reader_(reader) { }

      void Init() override;
      void Execute() override;
    
    private:
      const hardware::Time* time_;
      const inputRead::ExternalIoReader* reader_;
  };
}

#endif  // BUTTON_MANAGER_H_
