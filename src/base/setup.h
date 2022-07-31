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
            const static std::size_t N = 2;
            lights_and_rollers::base::Module* modules[N];
    };
}

#endif  // SETUP_H_
