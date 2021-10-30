#pragma once
#include "../Common/avrModule.hpp"
#include "uartControl.hpp"
#include "uartManager.hpp"
#include "inttypes.h"

class uartControlModule : public avrModule, public uartControl
{
public:
    uartControlModule(uartManager* uartManager);
    void Init() override;
    void Loop() override;
    void setWrite() override;
    void setRead() override;
    void send(const uint8_t& byte) override;
private:
    uartManager* manager;
    uint8_t byteToSend;
    bool isSending;
};
