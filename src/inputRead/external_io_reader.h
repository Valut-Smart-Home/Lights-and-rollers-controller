
#ifndef EXTERNAL_IO_READER_H_
#define EXTERNAL_IO_READER_H_

#include "../base/module.h"
#include "../base/twi_user.h"
#include "../hwd_managment/twi_manager.h"

namespace lights_and_rollers::inputRead {
  class ExternalIoReader : public base::Module, public base::TwiUser
  {
    public:
      ExternalIoReader(hwd_management::TwiManager* twi) : base::Module(base::Stage::kReadInputs), twi_(twi) { }

      void Init() override;
      void Execute() override;
    
      void TwiOnReady(bool last_command_success) override;
    
    private:
      const hwd_management::TwiManager* twi_;
  };
}

#endif  // EXTERNAL_IO_READER_H_
