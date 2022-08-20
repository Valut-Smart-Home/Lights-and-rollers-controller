#include <inttypes.h>
#include <gtest/gtest.h>

#include "../../src/hwd_managment/i2c_manager.h"
#include "../../src/base/i2c_user.h"
#include "../../src/hardware/i2c.h"

class TestUser : public lights_and_rollers::base::I2cUser {
    public:
        int on_ready_count;
        void I2cOnReady() override { on_ready_count++; }
};

class TestI2cHardware : public lights_and_rollers::hardware::I2c {
    public:
        void set_ready(bool value) {
            ready = value;
        }
};

TEST(I2cManager, CreateInstance) {
    TestI2cHardware i2c;
    lights_and_rollers::hwd_management::I2cManager i2cManager(&i2c);
}
