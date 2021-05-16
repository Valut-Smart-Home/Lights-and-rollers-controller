#pragma once
#include "inttypes.h"

class twiControl
{
public:
    virtual bool isReady();
    virtual const int8_t& lastError();
    virtual void write(const uint8_t* writeBuffer, uint8_t&& wCount);
    virtual void read(const uint8_t* address, uint8_t* readBuffer, uint8_t&& rCount);
};
