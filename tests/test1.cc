#include <inttypes.h>
#include <gtest/gtest.h>

uint8_t x() {
    return 12;
}

TEST(MojeTesty,TestPierwszy) {
    auto a = x();
    EXPECT_EQ(12, a);
}

