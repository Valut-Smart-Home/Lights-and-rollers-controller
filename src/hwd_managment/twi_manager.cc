#include "twi_manager.h"

namespace lights_and_rollers::hwd_management {
  void TwiManager::Execute()
  {
    if (currentUser_ == nullptr) {
      currentUser_ = firstUser_;
    }
    if (currentUser_ != nullptr) {
      currentUser_->TwiOnReady();
    }
  }

  void TwiManager::RegisterUser(base::TwiUser* user)
  {
    user->NextTwiUser = firstUser_;
    firstUser_ = user;
  }

  void TwiManager::NextUser()
  {
    if (currentUser_ != nullptr) {
      currentUser_ = currentUser_->NextTwiUser;
    }
  }

  void TwiManager::Read(uint8_t id, uint8_t address, uint8_t count)
  {

  }

  void TwiManager::Write(uint8_t id, uint8_t address, uint8_t count)
  {

  }
}
