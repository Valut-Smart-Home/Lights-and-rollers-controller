#pragma once
#include "inttypes.h"

class uartControl
{
public:
    virtual void setWrite();
    virtual void setRead();
    virtual void send(const uint8_t& byte);
};
