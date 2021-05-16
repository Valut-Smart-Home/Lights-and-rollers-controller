#include "twiControlModule.hpp"
#include <avr/io.h>

#pragma message ("TWI (PC4, PC5 pins) used by twiControlModule")

enum class twi_status : uint8_t
{
    Start_OK = 0x08,
    Repeated_Start_OK = 0x10,
    SLA_W_Transmited_ACK = 0x18,
    SLA_W_Transmited_NO_ACK = 0x20,
    Data_Transmited_ACK = 0x28,
    Data_Transmited_NO_ACK = 0x30,
    Arbitration_Lost = 0x38,
    SLA_R_Transmited_ACK = 0x40,
    SLA_R_Transmited_NO_ACK = 0x48,
    Data_Received_ACK = 0x50,
    Data_Received_NO_ACK = 0x58,
};

void twiControlModule::Init()
{
   TWBR = (F_CPU / 100000 - 16) / 2;
   TWCR = 
    (0 << TWINT) |
    (0 << TWEA) | (0 << TWSTA) | (0 << TWSTO) |
    (0 << TWWC) |
    (1 << TWEN) |
    (0 << TWIE);
}

inline void twi_start()
{
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA) | _BV(TWSTO);
}

inline void twi_stop()
{
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}

inline void twi_send()
{
    TWCR = _BV(TWINT) | _BV(TWEN);
}

inline void twi_send_ack()
{
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
}

inline uint8_t twi_isReady()
{
    return TWCR & _BV(TWINT);
}

inline uint8_t twi_getStatus()
{
    return TWSR & 0xF8;
}

void twiControlModule::Loop()
{
    auto check = [&](twi_status s) {
        if (twi_getStatus() != (uint8_t)s)
        {
            err = twi_getStatus() | 1;
            twi_stop();
            started = false;
        }
    };

    if (wPos == 0 && rPos == 0 && wCount != 0 && err == 0 && !started)
    {
        twi_start();
        started = true;
    }
    else if (twi_isReady())
    {
        if (wPos < wCount)
        {
            if (wPos == 0) check(twi_status::Start_OK);
            else if (wPos == 1) check(twi_status::SLA_W_Transmited_ACK);
            else check(twi_status::Data_Transmited_ACK);

            if (!err)
            {
                TWDR = writeBuffer[wPos++];
                twi_send();
            }
        } 
        else if (rPos < rCount)
        {
            if (wPos == 1) check(twi_status::SLA_R_Transmited_ACK);

            if (!err)
            {
                if (wPos++ > 1)
                    readBuffer[rPos++] = TWDR;
                
                if (rPos < rCount - 1)
                    twi_send_ack();
                else if (rPos < rCount)
                    twi_send();
            }
        }
        else if (started)
        {
            twi_stop();
            started = false;
        }
    }
}

bool twiControlModule::isReady()
{
    return wPos >= wCount && rPos == rCount && !started;
}

void twiControlModule::write(const uint8_t* writeBuffer, uint8_t&& wCount)
{
    this->writeBuffer = writeBuffer;
    this->wCount = wCount;
    this->wPos = 0;
    this->rCount = 0;
    this->rPos = 0;
    this->err = 0;
    this->started = false;
}

void twiControlModule::read(const uint8_t* address, uint8_t* readBuffer, uint8_t&& rCount)
{
    this->writeBuffer = address;
    this->wCount = 1;
    this->wPos = 0;
    this->readBuffer = readBuffer;
    this->rCount = rCount;
    this->rPos = 0;
    this->err = 0;
    this->started = false;
}

const int8_t& twiControlModule::lastError()
{
    return err;
}
