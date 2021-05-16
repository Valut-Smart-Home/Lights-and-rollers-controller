#pragma once
#include "avrModule.hpp"
#include "programTimer.hpp"
#include <inttypes.h>

class programTimerModule : public avrModule, public programTimer
{
private:
    uint8_t lastValue;
    unsigned long ticks;
public:
    programTimerModule();
    void Init() override;
    void Loop() override;
    unsigned long getTicks() const override;
    unsigned long toMs(const unsigned long& ticks) const override;
};
