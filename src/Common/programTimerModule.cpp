#include "programTimerModule.hpp"
#include <avr/io.h>

#pragma message ("Timer0 used by programTimerModule")

programTimerModule::programTimerModule()
{

}

void programTimerModule::Init() 
{
    TCCR0A =
        (0 << COM0A1) | (0 << COM0A0) | 
        (0 << COM0B1) | (0 << COM0B0) |
        (0 << WGM01) | (0 << WGM00);
    TCCR0B = 
        (0 << FOC0A) | (0 << FOC0B) |
        (0 << WGM02) |
        (1 << CS02) | (0 << CS01) | (1 << CS00); // 1024 prescaller
}

void programTimerModule::Loop()
{
    uint8_t curValue = TCNT0;
    ticks += curValue - lastValue;
    lastValue = curValue;
}

unsigned long programTimerModule::getTicks() const
{
    return ticks;
}

unsigned long programTimerModule::toMs(const unsigned long& ticks) const
{
    return ticks * 1024000 / F_CPU;
}
