#pragma once
#include "avrModule.hpp"
#include "uartManager.hpp"
#include "twiControl.hpp"
#include "programTimer.hpp"
#include "inttypes.h"

class simpleManager : public avrModule, public uartManager
{
public:
    simpleManager(twiControl* twiControl, programTimer* programTimer);
    void Init() override;
    void Loop() override;
    void setUartControl(uartControl* uartControl) override;
    void uartOnRead(int8_t readedByte) override;
    void uartOnWrite() override;
private:
    twiControl* twi;
    const programTimer* timer;
    uartControl* uart;
};
