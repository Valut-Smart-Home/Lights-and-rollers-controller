#include <inttypes.h>
#include <gtest/gtest.h>

#include "../../src/hwd_managment/twi_manager.h"
#include "../../src/base/twi_user.h"
#include "../../src/hardware/twi.h"

class TestUser : public lights_and_rollers::base::TwiUser {
  public:
    int on_ready_count{0};
    void TwiOnReady() override { on_ready_count++; }
};

class TestTwiHardware : public lights_and_rollers::hardware::Twi {
  public:
    void set_ready(bool value) {
      state_ = !value;
    }
    void set_ok(bool value) {
      ok_ = value;
    }
};

TEST(TwiManager, CreateInstance) {
  TestTwiHardware twi;
  lights_and_rollers::hwd_management::TwiManager twiManager(&twi);
}

TEST(RwiManager, UsersLoop) {
  TestTwiHardware twi;
  TestUser user1, user2;
  lights_and_rollers::hwd_management::TwiManager twiManager(&twi);
  twiManager.Init();
  twiManager.RegisterUser(&user1);
  twiManager.RegisterUser(&user2);

  twiManager.Execute();
  twiManager.Execute();
  twiManager.NextUser();
  twiManager.Execute();
  twiManager.NextUser();

  ASSERT_EQ(2, user1.on_ready_count);
  ASSERT_EQ(1, user2.on_ready_count);

  twiManager.Execute();
  twiManager.NextUser();

  ASSERT_EQ(3, user1.on_ready_count);
  ASSERT_EQ(1, user2.on_ready_count);
}
