#ifndef PARTS_MODULES_CENTRIFUGAL_SLINGSHOT_HPP
#define PARTS_MODULES_CENTRIFUGAL_SLINGSHOT_HPP

#include "simple_trigger_module.hpp"

namespace parts {
  class CentrifugalSlingshot : public SimpleTriggerModule {
  private:
    double efficiency;
    double multiplier;
  protected:
  public:
    CentrifugalSlingshot(int signal_code, double cooldown,
                         double multiplier = 50.0, double efficiency = 1.0);
    virtual void trigger() override;
  };
}

#endif
