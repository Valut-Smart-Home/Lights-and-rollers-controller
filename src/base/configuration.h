#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

namespace lights_and_rollers::base {
  class Configuration
  {  
    public:
      void InitRead();
  };
  
  Configuration configuration = Configuration();
}

#endif  // CONFIGURATION_H_