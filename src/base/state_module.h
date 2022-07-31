#ifndef STATE_MODULE_H_
#define STATE_MODULE_H_

namespace lights_and_rollers::base {
  class StateModule
  {
    public:
      virtual void Recover();
      virtual void Save();
  };
}

#endif  // STATE_MODULE_H_