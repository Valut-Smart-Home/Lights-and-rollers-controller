#include "simpleManager.hpp"
#include "../Communication/uartManager.hpp"
#include "../Communication/twiControl.hpp"
#include "inttypes.h"
#include "programTimer.hpp"

#include <avr/io.h>

const unsigned int coilOperationalTimeMs = 10;

uint8_t buttonsNow[]{ 0xFF, 0xFF, 0xFF, 0xFF };
uint8_t buttonsLastRead[]{ 0xFF, 0xFF, 0xFF, 0xFF };
uint8_t buttonsErr[]{ 0, 0, 0, 0 };
uint16_t light[16]{ 0 };
uint8_t buttonPos{0}, lightPos{0};
uint8_t writeCoilsBuff[2][2]{ {0x00, 0x00}, {0x00, 0x00} };

uint8_t buttonCounter[4][8] {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
};
uint16_t buttonConnection[4][8]{
    { 
        {(1 << 3)}, 
        {(1 << 4) | (1 << 5)}, 
        {(1 << 10) | (1 << 11) | (1 << 12) | (1 << 13)}, 
        {(1 << 4) | (1 << 5)}, 
        {0xFFFF}, 
        {0xFFFF}, 
        {(1 << 8) | (1 << 9)}, 
        {(1 << 0) | (1 << 1)}, 
    },
    { 
        {(1 << 8) | (1 << 9)}, 
        {(1 << 10) | (1 << 11)}, 
        {0}, 
        {0}, 
        {0}, 
        {0}, 
        {0}, 
        {0}, 
    },
    { 
        {(1 << 4) | (1 << 5)}, 
        {(1 << 2)}, 
        {0}, 
        {0}, 
        {(1 << 1)}, 
        {(1 << 0) | (1 << 1)}, 
        {0}, 
        {0}, 
    },
    { 
        {0}, 
        {0}, 
        {(1 << 10) | (1 << 11)}, 
        {(1 << 12) | (1 << 13)}, 
        {(uint16_t)(1 << 15)}, 
        {(1 << 14) | (uint16_t)(1 << 15)}, 
        {0}, 
        {0}, 
    },
};

struct rollersConnectionStruct {
    uint8_t buttonGroup;
    uint8_t buttonUpPin;
    uint8_t buttonDownPin;
    uint8_t outputGroup;
    uint8_t outputDirectionPin;
    uint8_t outputRunPin;
    unsigned long pushed{0};
    uint8_t mask{0xFF};

    rollersConnectionStruct(
        const uint8_t && buttonGroup,
        const uint8_t && buttonUpPin,
        const uint8_t && buttonDownPin,
        const uint8_t && outputGroup,
        const uint8_t && outputDirectionPin,
        const uint8_t && outputRunPin) : 
        buttonGroup(buttonGroup),
        buttonUpPin(buttonUpPin),
        buttonDownPin(buttonDownPin),
        outputGroup(outputGroup),
        outputDirectionPin(outputDirectionPin),
        outputRunPin(outputRunPin)
    { }
};

enum class smState: uint8_t
{
    Init1,
    Init2,
    Reading,
    InitSending,
    Sending,
    InitCoilSending,
    CoilSending
} state;

const uint8_t Light_Setup[]{ 0x80, 0x00, 0x20, 0x04 };
const uint8_t ReadButtons[]{ 0x41, 0x43, 0x45, 0x47 };
const uint8_t WriteCoils[]{ 0x48, 0x4A };

rollersConnectionStruct rollers[6]{ 
    rollersConnectionStruct{(uint8_t)1,(uint8_t)2,(uint8_t)3,(uint8_t)0,(uint8_t)1,(uint8_t)0}, 
    rollersConnectionStruct{(uint8_t)3,(uint8_t)6,(uint8_t)7,(uint8_t)1,(uint8_t)1,(uint8_t)0}, 
    rollersConnectionStruct{(uint8_t)3,(uint8_t)0,(uint8_t)1,(uint8_t)1,(uint8_t)3,(uint8_t)2}, 
    rollersConnectionStruct{(uint8_t)1,(uint8_t)5,(uint8_t)4,(uint8_t)1,(uint8_t)5,(uint8_t)4}, 
    rollersConnectionStruct{(uint8_t)2,(uint8_t)2,(uint8_t)3,(uint8_t)0,(uint8_t)3,(uint8_t)2}, 
    rollersConnectionStruct{(uint8_t)1,(uint8_t)6,(uint8_t)7,(uint8_t)0,(uint8_t)5,(uint8_t)4}, 
};

simpleManager::simpleManager(twiControl* twiControl, programTimer* programTimer):
    twi(twiControl),
    timer(programTimer)
{ }

void simpleManager::setUartControl(uartControl* uartControl) 
{
    uart = uartControl;
}
    
void simpleManager::Init() 
{
    state = smState::Init1;
}

struct lightCommandStruct
{
    const uint8_t start[2]{ 0x80, 0x06 };
    uint16_t values[32];
} lightCommand;

const uint16_t LedFull_ON = 0x1000;
const uint16_t LedFull_OFF = 0x0000;
void makeLightCommand()
{
    uint16_t current = 0;
    uint8_t i, j;
    j = 0;
    for (i = 0; i < 8; ++i)
    {
        if (light[i] == 0x0FFFF)
        {
            lightCommand.values[j++] = LedFull_ON;
            lightCommand.values[j++] = LedFull_OFF;
        }
        else
        {
            lightCommand.values[j++] = current;
            current += light[i];
            current &= 0x0FFF;
            lightCommand.values[j++] = current;
        }
    }
    current = 0;
    for (i = 8; i < 16; ++i)
    {
        if (light[i] == 0x0FFFF)
        {
            lightCommand.values[j++] = LedFull_ON;
            lightCommand.values[j++] = LedFull_OFF;
        }
        else
        {
            lightCommand.values[j++] = current;
            current += light[i];
            current &= 0x0FFF;
            lightCommand.values[j++] = current;
        }
    }
}

bool switchLights(const uint16_t& lights)
{
    bool init{false}, isOn{false};
    for (uint8_t i = 0; i < 16; ++i)
    {
        if (lights & (1 << i))
        {
            if (!init)
            {
                init = true;
                isOn = light[i] == 0;
            }
            if (isOn)
                light[i] = 0xFFFF;
            else
                light[i] = 0;
        }
    }
    return init;
}

inline void doCoilChanges(bool changed[2])
{
    for (uint8_t i = 0; i < 2; ++i)
    {
        if (changed[i])
        {
            uint8_t v = 0xFF;
            for (auto roller: rollers)
            {
                if (roller.outputGroup == i)
                    v &= roller.mask;
            }
            writeCoilsBuff[i][0] = WriteCoils[i];
            writeCoilsBuff[i][1] = v;
        }
    }
}

void checkCoilChanges()
{
    if (state == smState::Reading)
    {
        for (auto v: writeCoilsBuff)
        {
            if (v[0])
            {
                state = smState::InitCoilSending;
                return;
            }
        }
    }
}

inline void coilsResponse(const programTimer& timer)
{
    bool changed[2] = {false, false};

    for (auto roller: rollers)
    {
        if (roller.buttonGroup == buttonPos)
        {
            uint8_t& btnUpCnt = buttonCounter[buttonPos][roller.buttonUpPin];
            uint8_t& btnDownCnt = buttonCounter[buttonPos][roller.buttonDownPin];

            if (btnUpCnt == 3)
            {
                uint8_t outDirPinMask = 1 << roller.outputDirectionPin;

                if (roller.mask & outDirPinMask)
                {
                    roller.mask &= ~outDirPinMask;
                    roller.pushed = timer.getTicks();
                    changed[roller.outputGroup] = true;
                }
                else if (timer.toMs(timer.getTicks() - roller.pushed) > 2 * coilOperationalTimeMs)
                {
                     uint8_t outRunPinMask = 1 << roller.outputRunPin;

                     if (roller.mask & outRunPinMask)
                     {
                         roller.mask &= ~outRunPinMask;
                         changed[roller.outputGroup] = true;
                     }
                }
            }
            else if (btnDownCnt == 3)
            {
                uint8_t outDirPinMask = 1 << roller.outputDirectionPin;

                if (!(roller.mask & outDirPinMask))
                {
                    roller.mask |= outDirPinMask;
                    roller.pushed = timer.getTicks();
                    changed[roller.outputGroup] = true;
                }
                else if (timer.toMs(timer.getTicks() - roller.pushed) > 2 * coilOperationalTimeMs)
                {
                    uint8_t outRunPinMask = 1 << roller.outputRunPin;

                    if (roller.mask & outRunPinMask)
                    {
                        roller.mask &= ~outRunPinMask;
                        changed[roller.outputGroup] = true;
                    }
                }
            }
            else
            {
                uint8_t outRunPinMask = 1 << roller.outputRunPin;
                
                if (!(roller.mask & outRunPinMask))
                {
                    roller.mask |= outRunPinMask;
                    roller.pushed = timer.getTicks();
                    changed[roller.outputGroup] = true;
                }
            }
        }
    }

    doCoilChanges(changed);
}

void takeResponse()
{
    buttonsLastRead[buttonPos] &= buttonsNow[buttonPos];
    for (uint8_t i = 0; i < 8; ++i)
    {
        if (buttonsNow[buttonPos] & (1 << i))
            buttonCounter[buttonPos][i] = 0;
        else
        {
            uint8_t& btnCnt = buttonCounter[buttonPos][i];

            if (btnCnt <= 3)
                ++btnCnt;
            if (btnCnt == 3)
            {
                const auto connections = buttonConnection[buttonPos];

                if (switchLights(connections[i]))
                    state = smState::InitSending;
            }
        }
    }
}

void simpleManager::Loop() 
{
    const uint8_t& err = twi->lastError();
    if (twi->isReady() || err)
    {
        switch (state)
        {
        case smState::Init1:
            twi->write(Light_Setup, sizeof(Light_Setup));
            state = smState::Init2;
            break;
        case smState::Init2:
            if (err) 
                state = smState::Init1;
            else
                state = smState::Sending;
            break;
        case smState::Reading:
            buttonsErr[buttonPos] = err;
            if (!err)
            {
                takeResponse();
                coilsResponse(*this->timer);
            }
            checkCoilChanges();
            if (++buttonPos >= sizeof(buttonsNow))
                buttonPos = 0;
            twi->read(&ReadButtons[buttonPos], &buttonsNow[buttonPos], 1);
            break;
        case smState::InitSending:
            buttonsErr[buttonPos] = err;
            if (!err)
            {
                takeResponse();
                coilsResponse(*this->timer);
            }
            makeLightCommand();
            twi->write((uint8_t*)&lightCommand, sizeof(lightCommand));
            state = smState::Sending;
            break;
        case smState::Sending:
            if (++buttonPos >= sizeof(buttonsNow))
                buttonPos = 0;
            twi->read(&ReadButtons[buttonPos], &buttonsNow[buttonPos], 1);
            state = smState::Reading;
            break;
        case smState::InitCoilSending:
            buttonsErr[buttonPos] = err;
            if (!err)
            {
                takeResponse();
                coilsResponse(*this->timer);
            }
            if (writeCoilsBuff[0][0])
                twi->write((uint8_t*)&writeCoilsBuff[0], sizeof(writeCoilsBuff[0]));
            else
                twi->write((uint8_t*)&writeCoilsBuff[1], sizeof(writeCoilsBuff[1]));
            state = smState::Sending;
            break;
        case smState::CoilSending:
            if (writeCoilsBuff[0][0])
            {
                writeCoilsBuff[0][0] = 0;
                writeCoilsBuff[0][1] = 0;
            }
            else
            {
                writeCoilsBuff[1][0] = 0;
                writeCoilsBuff[1][1] = 0;
            }
            
            if (++buttonPos >= sizeof(buttonsNow))
                buttonPos = 0;
            twi->read(&ReadButtons[buttonPos], &buttonsNow[buttonPos], 1);
            state = smState::Reading;
            break;
        default:
            break;
        }
    }
}

uint16_t* laddr{light};
uint8_t bpos{0};
void simpleManager::uartOnRead(int8_t readedByte) 
{
    if (readedByte == 's')
    {
        if (state == smState::Reading)
            state = smState::InitSending;
    }
    else if (readedByte == 'r')
    {
        bpos = 0;
        uart->setWrite();
        uartOnWrite();
    }
    else if (readedByte < 16)
    {
        laddr = light + readedByte;
    }
    else if (readedByte < 32)
    {
        readedByte -= 16;
        *laddr = 0x0FFF * readedByte / 16;
    }
}

void simpleManager::uartOnWrite() 
{
    if (bpos < 4)
    {
        uart->send(buttonsLastRead[bpos]);
        if (!buttonsErr[bpos])
            buttonsLastRead[bpos] = buttonsNow[bpos];
    }
    else if (bpos < 8)
        uart->send(buttonsErr[bpos - 4]);
    else
        uart->setRead();
    ++bpos;
}
