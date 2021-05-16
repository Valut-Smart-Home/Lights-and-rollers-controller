#include "uartControlModule.hpp"
#include "uartManager.hpp"
#include "inttypes.h"
#include <avr/io.h>

#pragma message ("UART0 (PD0, PD1 pins) + PORTD2 used by uartControlModule")

uartControlModule::uartControlModule(uartManager* uartManager)
{
    isSending = false;
    manager = uartManager;
    manager->setUartControl(this);
}

inline void uartControlModule::setRead()
{
    UCSR0B &= ~(1 << TXEN0);
    PORTD &= ~(1 << PORTD2);
    UCSR0B |= (1 << RXEN0);
}

inline void uartControlModule::setWrite()
{
    UCSR0B &= ~(1 << RXEN0);
    PORTD |= (1 << PORTD2);
    UCSR0B |= (1 << TXEN0);
}

inline uint8_t isWrite()
{
    return PORTD & (1 << PORTD2);
}

inline uint8_t isReadReady()
{
    return UCSR0A & (1 << RXC0);
}

inline uint8_t isWriteReady()
{
    return UCSR0A & (1 << UDRE0);
}

void uartControlModule::Init()
{
    DDRD |= 1 << PORTD2;

    UBRR0 = (F_CPU / 16) / 9600 - 1;
    UCSR0A = (0 << U2X0) | (0 << MPCM0);
    UCSR0B = (0 << RXCIE0) | (0 << TXCIE0) | (0 << UDRIE0) |
        (0 << RXEN0) | (0 << TXEN0) |
        (0 << UCSZ02);
    UCSR0C = (0 << UMSEL01) | (0 << UMSEL01) |
        (0 << UPM01) | (0 << UPM00) |
        (0 << USBS0) |
        (1 << UCSZ01) | (1 << UCSZ00) |
        (0 << UCPOL0);

    setRead();
}

void uartControlModule::send(const uint8_t & byte)
{
    byteToSend = byte;
}

void uartControlModule::Loop()
{
    if (isWrite())
    {
        if (isWriteReady())
        {
            if (isSending)
            {
                isSending = false;
                manager->uartOnWrite();
            }
            else
            {
                isSending = true;
                UDR0 = byteToSend;   
            }
        }
    }
    else
    {
        if (isReadReady())
        {
            manager->uartOnRead(UDR0);
        }
    }
}