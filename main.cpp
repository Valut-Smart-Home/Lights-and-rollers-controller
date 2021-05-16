#include <avr/io.h>
#include "avrModule.hpp"
#include "programTimerModule.hpp"
#include "twiControlModule.hpp"
#include "uartControlModule.hpp"
#include "simpleManager.hpp"

int main()
{
    programTimerModule programTimerModule{};
    twiControlModule twiControlModule{};
    simpleManager simpleManager{&twiControlModule, &programTimerModule};
    uartControlModule uartControlModule{&simpleManager};

    avrModule* modules[]{ 
        &programTimerModule,
        &twiControlModule,
        &uartControlModule,
        &simpleManager,
    };

    for (auto mod: modules)
        mod->Init();
    while (true)
        for (auto mod: modules)
            mod->Loop();
}
