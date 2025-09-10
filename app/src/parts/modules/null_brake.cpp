#include "parts/modules/null_brake.hpp"
#include "parts/cores/ship_core.hpp"
#include <algorithm>

namespace parts {

  NullBrake::NullBrake(int signal_code, double cooldown,
                       double efficiency, double angular_efficiency)
  : SimpleTriggerModule(signal_code, cooldown),
    efficiency(std::clamp(efficiency, 0.0, 1.0)),
    angular_efficiency(std::clamp(angular_efficiency, 0.0, 1.0)) {}

  void NullBrake::trigger() {
    core->setVelocity(core->getVelocity() * (1 - efficiency));
    core->setAngularVelocity(core->getAngularVelocity() * (1 - angular_efficiency));
  }
}
