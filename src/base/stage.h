#ifndef STAGE_H_
#define STAGE_H_

namespace lights_and_rollers::base {
  enum class Stage {
    kHardwareInteraction,
    kReadInputs,
    kInterpretateInputs,
    kExecuteProgram,
    kSetOutputs,
    kCommunication,
    kApplyChanges,
  };
}

#endif  // STAGE_H_