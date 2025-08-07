#include "parts/modules/module.hpp"

namespace parts {
  void Module::setCore(SpaceshipCore& core) {
    this->core = &core;
  }
}
