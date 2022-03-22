#include "simpleManager.hpp"
#include "../Communication/uartManager.hpp"
#include "../Communication/twiControl.hpp"
#include "inttypes.h"
#include "programTimer.hpp"

#include <avr/io.h>

uint8_t buttonsNow[]{ 0xFF };
uint8_t buttonsLastRead[]{ 0xFF };
uint8_t buttonsErr[]{ 0 };
uint16_t light[16]{ 0 };

uint8_t buttonCounter[1][8] {
    {0,0,0,0,0,0,0,0},
};
uint16_t buttonConnection[1][8]{
    { 
        {(1 << 6) | (1 << 7)| (1 << 5)},
        {(1 << 4)}, 
        {(uint16_t)(1 << 15)}, 
        {(1 << 13)}, 
        {(1 << 12) | (1 << 14)}, 
        {(1 << 0) | (1 << 1) | (1 << 8) | (1 << 9)}, 
        {(1 << 0) | (1 << 1) | (1 << 8) | (1 << 9)}, 
        {(1 << 10) | (1 << 11)}, 
    }
};

enum class smState: uint8_t
{
    Init1,
    Init2,
    Reading,
    InitSending,
    Sending,
} state;

const uint8_t Light_Setup[]{ 0x80, 0x00, 0x20, 0x04 };
const uint8_t ReadButtons[]{ 0x41 };

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

void takeResponse()
{
    buttonsLastRead[0] &= buttonsNow[0];
    for (uint8_t i = 0; i < 8; ++i)
    {
        if (buttonsNow[0] & (1 << i))
            buttonCounter[0][i] = 0;
        else
        {
            uint8_t& btnCnt = buttonCounter[0][i];

            if (btnCnt <= 3)
                ++btnCnt;
            if (btnCnt == 3)
            {
                const auto connections = buttonConnection[0];

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
            buttonsErr[0] = err;
            if (!err)
            {
                takeResponse();
            }
            twi->read(&ReadButtons[0], &buttonsNow[0], 1);
            break;
        case smState::InitSending:
            buttonsErr[0] = err;
            if (!err)
            {
                takeResponse();
            }
            makeLightCommand();
            twi->write((uint8_t*)&lightCommand, sizeof(lightCommand));
            state = smState::Sending;
            break;
        case smState::Sending:
            twi->read(&ReadButtons[0], &buttonsNow[0], 1);
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
