#ifndef SETUP_H_
#define SETUP_H_

#include <stdlib.h>

#include "module.h"

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
            const static std::size_t N = 4;
            lights_and_rollers::base::Module* modules[N];
            std::size_t moduleCounter = 0;
    };
}

#endif  // SETUP_H_
