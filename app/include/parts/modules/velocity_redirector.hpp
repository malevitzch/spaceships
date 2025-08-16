#ifndef PARTS_MODULES_VELOCITY_REDIRECTOR_HPP
#define PARTS_MODULES_VELOCITY_REDIRECTOR_HPP
#include "simple_trigger_module.hpp"

namespace parts {

  class VelocityRedirector : public SimpleTriggerModule {
  private:
  protected:
    double efficiency;
  public:
    VelocityRedirector(int signal_code,
                       double cooldown=5,
                       double efficiency=1);
    virtual void trigger() override;
  };

}

#endif
