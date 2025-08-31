#include "parts/modules/simple_trigger_module.hpp"

#include <SFML/System/Time.hpp>

namespace parts {

  SimpleTriggerModule::SimpleTriggerModule(int signal_code,
                                           double cooldown) :
    sig_code(signal_code), cooldown(cooldown) {}

  void SimpleTriggerModule::failed() {}

  void SimpleTriggerModule::processSignal(Signal& signal) {
    if(signal.code == sig_code &&
       timer.getElapsedTime().asSeconds() >= cooldown) {
      timer.restart();
      trigger();
    } else {
      failed();
    }
  }

  void SimpleTriggerModule::reset() {
    timer.restart();
  }

  void SimpleTriggerModule::setSignal(int new_sig_code) {
    sig_code = new_sig_code;
  }
}
