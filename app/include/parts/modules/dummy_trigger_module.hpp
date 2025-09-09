#ifndef PARTS_MODULES_DUMMY_TRIGGER_MODULE_HPP
#define PARTS_MODULES_DUMMY_TRIGGER_MODULE_HPP

#include "trigger_module.hpp"

namespace parts {
  class DummyTriggerModule : public TriggerModule {
  private:
  public:
    DummyTriggerModule() = default;
    virtual void processSignal(Signal& signal) override;
  };
}

#endif
