#include "parts/modules/velocity_redirector.hpp"
#include "parts/cores/ship_core.hpp"
#include "utility/vec2d.hpp"

namespace parts {

  VelocityRedirector::VelocityRedirector(int signal_code,
                                         double cooldown,
                                         double efficiency)
  : SimpleTriggerModule(signal_code, cooldown), efficiency(efficiency) {
  }
  void VelocityRedirector::trigger() {
    auto& core = getCore();
    util::Vec2d velocity = core.getVelocity();
    double target_magnitude = velocity.magnitude() * efficiency;
    util::Vec2d redirected_vector = util::Vec2d(target_magnitude, core.getAngle());
    getCore().setVelocity(redirected_vector + velocity * (1 - efficiency));
  }

}
