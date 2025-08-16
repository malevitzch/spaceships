#include "parts/modules/module.hpp"

namespace parts {
  void Module::setCore(ShipCore& core) {
    this->core = &core;
  }
  ShipCore& Module::getCore() const {
    return *core;
  }

  void Module::reset() {}
}
