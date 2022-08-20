#include "../../src/hardware/time.h"

void lights_and_rollers::hardware::Time::Init()
{ }

void lights_and_rollers::hardware::Time::Execute()
{ }

const unsigned long& lights_and_rollers::hardware::Time::ticks()
{
    return currentTicks;
}

unsigned long lights_and_rollers::hardware::Time::msToTicks(const unsigned long&& ms)
{
    return ms;
}
