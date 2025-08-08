#ifndef PARTS_MODULES_SIMPLE_TRIGGER_MODULE_HPP
#define PARTS_MODULES_SIMPLE_TRIGGER_MODULE_HPP
#include "trigger_module.hpp"
#include <SFML/System/Clock.hpp>

namespace parts {

  class SimpleTriggerModule : public TriggerModule {
  private:
  protected:
    sf::Clock timer;
    int sig_code;
    double cooldown;
  public:
    SimpleTriggerModule(int signal_code, double cooldown);
    virtual void trigger() = 0;
    virtual void processSignal(Signal& signal) override;

    virtual void reset() override;
  };

}

#endif
