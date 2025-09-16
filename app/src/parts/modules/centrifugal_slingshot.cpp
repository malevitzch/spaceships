#include "parts/modules/centrifugal_slingshot.hpp"
#include "parts/cores/ship_core.hpp"
#include "utility/vec2d.hpp"
#include <cmath>

namespace parts {
  CentrifugalSlingshot::CentrifugalSlingshot(int signal_code, double cooldown,
                                             double multiplier, double efficiency)
  : SimpleTriggerModule(signal_code, cooldown), efficiency(efficiency), multiplier(multiplier) {}

  void CentrifugalSlingshot::trigger() {
    double magnitude = efficiency * std::fabs(core->getAngularVelocity()) * multiplier;

    core->setAngularVelocity(core->getAngularVelocity() * (1.0 - efficiency));
    util::Vec2d boost(magnitude, core->getAngle());
    core->addVelocity(boost);
  }
}
