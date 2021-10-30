#pragma once

class programTimer
{
public:
    virtual unsigned long getTicks() const;
    virtual unsigned long toMs(const unsigned long& ticks) const;
};
