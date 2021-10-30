#include <avr/io.h>
#include "Common/avrModule.hpp"
#include "Common/programTimerModule.hpp"
#include "Communication/twiControlModule.hpp"
#include "Communication/uartControlModule.hpp"
#include "Common/simpleManager.hpp"

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
