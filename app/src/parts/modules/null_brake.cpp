#include "parts/modules/null_brake.hpp"
#include "parts/cores/ship_core.hpp"

namespace parts {

  NullBrake::NullBrake(int signal_code, double cooldown)
  : SimpleTriggerModule(signal_code, cooldown) {}
  void NullBrake::trigger() {
    core->setVelocity({0, 0});
    core->setAngularVelocity(0);
  }
}
