#ifndef STAGE_H_
#define STAGE_H_

namespace lights_and_rollers::base {
  enum class Stage {
    kHardwareInteraction,
    kHardwareMangement,
    kReadInputs,
    kProcessInputs,
    kExecuteProgram,
    kProcessOutputs,
    kSetOutputs,
    kCommunication,
    kApplyChanges,
  };
}

#endif  // STAGE_H_