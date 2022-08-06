#include "../../src/hardware/uart.h"

void lights_and_rollers::hardware::Uart::Init()
{ }

void lights_and_rollers::hardware::Uart::Execute()
{ }

bool lights_and_rollers::hardware::Uart::is_send_ready()
{
    return false;
}

void lights_and_rollers::hardware::Uart::to_send(const uint8_t &byte)
{ }

bool lights_and_rollers::hardware::Uart::is_new_byte()
{
    return false;
}

const uint8_t& lights_and_rollers::hardware::Uart::last_byte_readed() 
{ 
    return *(new uint8_t);
}
