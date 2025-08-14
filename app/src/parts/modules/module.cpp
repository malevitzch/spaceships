#include "parts/modules/module.hpp"

namespace parts {
  void Module::setCore(ShipCore& core) {
    this->core = &core;
  }
  void Module::reset() {}
}
