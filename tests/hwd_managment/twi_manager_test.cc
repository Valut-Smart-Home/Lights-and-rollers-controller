#include <inttypes.h>
#include <gtest/gtest.h>

#include "../../src/hwd_managment/twi_manager.h"
#include "../../src/base/twi_user.h"
#include "../../src/hardware/twi.h"

class TestUser : public lights_and_rollers::base::TwiUser {
    public:
        int on_ready_count;
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
