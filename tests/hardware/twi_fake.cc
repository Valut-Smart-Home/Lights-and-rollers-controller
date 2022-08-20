#include "../../src/hardware/twi.h"

void lights_and_rollers::hardware::Twi::Init()
{ }

void lights_and_rollers::hardware::Twi::Execute()
{ }

bool lights_and_rollers::hardware::Twi::is_ready()
{
    return !state_;
}

bool lights_and_rollers::hardware::Twi::is_ok()
{
    return ok_;
}

void lights_and_rollers::hardware::Twi::ExecuteBuffer(const uint8_t&& count)
{ }
