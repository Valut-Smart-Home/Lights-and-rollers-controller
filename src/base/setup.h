#ifndef SETUP_H_
#define SETUP_H_

#include <stdlib.h>

#include "module.h"

#if !__AVR__
    using size_t = std::size_t;
#endif

namespace lights_and_rollers::base {
    class Setup
    {
        public: 
            void CreateObjects();
            void ReadConfiguration();
            void InitModules();
            void SetupPowerOut();
            void ExecuteModules();
        protected:
            const static size_t N = 5;
            lights_and_rollers::base::Module* modules[N];
            size_t moduleCounter = 0;
    };
}

#endif  // SETUP_H_
