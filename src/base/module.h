#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "stage.h"

namespace lights_and_rollers::base {
  class Module
  {
    public:  
      Module(Stage stage): stage(stage) {};
      
      virtual void Init() {};
      virtual void Execute() {};

      const Stage stage;
  };
}

#endif  // CONFIGURATION_H_