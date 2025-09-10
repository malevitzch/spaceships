#ifndef PARTS_MODULES_NULL_BRAKE_HPP
#define PARTS_MODULES_NULL_BRAKE_HPP

#include "simple_trigger_module.hpp"

namespace parts {
  class NullBrake : public SimpleTriggerModule {
  private:
    double efficiency;
    double angular_efficiency;
  protected:
  public:
    NullBrake(int signal_code, double cooldown,
              double efficiency = 1.0, double angular_efficiency = 1.0);
    virtual void trigger() override;
  };
}

#endif
