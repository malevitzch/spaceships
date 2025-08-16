#ifndef PARTS_MODULES_NULL_BRAKE_HPP
#define PARTS_MODULES_NULL_BRAKE_HPP

#include "simple_trigger_module.hpp"

namespace parts {
  class NullBrake : public SimpleTriggerModule {
  private:
  protected:
  public:
    NullBrake(int signal_code, double cooldown = 10.0);
    virtual void trigger() override;
  };
}

#endif
