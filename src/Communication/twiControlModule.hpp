#pragma once
#include "../Common/avrModule.hpp"
#include "twiControl.hpp"
#include <inttypes.h>

class twiControlModule : public avrModule, public twiControl
{
public:
    void Init() override;
    void Loop() override;
    bool isReady() override;
    void write(const uint8_t* writeBuffer, uint8_t&& wCount) override;
    void read(const uint8_t* address, uint8_t* readBuffer, uint8_t&& rCount) override;
    const int8_t& lastError() override;
private:
    const uint8_t* writeBuffer;
    uint8_t* readBuffer;
    uint8_t wPos = 0, wCount = 0;
    uint8_t rPos = 0, rCount = 0;
    bool started = false;
    int8_t err;
};
