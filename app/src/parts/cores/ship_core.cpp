#include "core/game.hpp"
#include "parts/cores/ship_core.hpp"
#include "physics/physics_object.hpp"
#include "physics/physics_transform.hpp"
#include "utility/angle.hpp"

namespace parts {
  using physics::CappedTransform;

  void ShipCore::broadcastSignal(int code) {
    broadcastSignal(Signal(code));
  }
  void ShipCore::broadcastSignal(int code, std::vector<std::string> args) {
    broadcastSignal(Signal(code, args));
  }
  void ShipCore::broadcastSignal(Signal signal) {
    for(auto& module : trigger_modules) {
      module->processSignal(signal);
    }
  }

  void ShipCore::addTriggerModule(std::unique_ptr<TriggerModule> module) {
    module->setCore(*this);
    trigger_modules.push_back(std::move(module));
  }

  ShipCore::ShipCore() :
    PhysicsObject(std::make_unique<CappedTransform>(10000, 15)) {}

  void ShipCore::resetState() {
    physics::PhysicsObject::resetTransform();
    PhysicsObject::setAngle(util::degrees(-90));
  }

  void ShipCore::setBattle(core::Battle* battle) {
    this->battle = battle;
  }
  core::Battle& ShipCore::getBattle() {
    return *battle;
  }

}
