#pragma once
#include "inttypes.h"
#include "uartControl.hpp"

class uartManager
{
public:
    virtual void setUartControl(uartControl* uartControl);
    virtual void uartOnRead(int8_t readedByte);
    virtual void uartOnWrite();
};
