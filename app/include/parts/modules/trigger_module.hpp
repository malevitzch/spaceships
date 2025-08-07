#ifndef PARTS_MODULES_TRIGGER_MODULE_HPP
#define PARTS_MODULES_TRIGGER_MODULE_HPP

#include "parts/modules/module.hpp"
#include "parts/signal.hpp"

namespace parts {
  class TriggerModule : public Module {
  private:
  protected:
  public:
    virtual void processSignal(Signal& signal);
  };
}
#endif
