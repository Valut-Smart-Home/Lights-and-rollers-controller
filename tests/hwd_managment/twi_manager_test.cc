#include <inttypes.h>
#include <gtest/gtest.h>

#include "../../src/hwd_managment/twi_manager.h"
#include "../../src/base/twi_user.h"
#include "../../src/hardware/twi.h"

class TestUser : public lights_and_rollers::base::TwiUser {
  public:
    int on_ready_count{0};
    void TwiOnReady(bool last_command_success) override { on_ready_count++; }
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

TEST(TwiManager, UsersLoop) {
  TestTwiHardware twi;
  TestUser user1, user2;
  lights_and_rollers::hwd_management::TwiManager twiManager(&twi);
  twiManager.Init();
  twiManager.RegisterUser(&user2);
  twiManager.RegisterUser(&user1);

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

TEST(TwiManager, WaitingForReady) {
  TestTwiHardware twi;
  TestUser user;
  lights_and_rollers::hwd_management::TwiManager twiManager(&twi);
  twiManager.Init();
  twiManager.RegisterUser(&user);

  twiManager.Execute();
  ASSERT_EQ(1, user.on_ready_count);

  twi.set_ready(false);
  twiManager.Execute();
  ASSERT_EQ(1, user.on_ready_count);

  twi.set_ready(true);
  twiManager.Execute();
  ASSERT_EQ(2, user.on_ready_count);
}
