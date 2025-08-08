#include "parts/cores/spaceship_core.hpp"
#include "physics/physics_object.hpp"
#include "physics/physics_transform.hpp"
#include "utility/angle.hpp"

namespace parts {
  using physics::CappedTransform;

  void SpaceshipCore::broadcastSignal(int code) {
    broadcastSignal(Signal(code));
  }
  void SpaceshipCore::broadcastSignal(int code, std::vector<std::string> args) {
    broadcastSignal(Signal(code, args));
  }
  void SpaceshipCore::broadcastSignal(Signal signal) {
    for(auto& module : trigger_modules) {
      module->processSignal(signal);
    }
  }

  void SpaceshipCore::addTriggerModule(std::unique_ptr<TriggerModule> module) {
    module->setCore(*this);
    trigger_modules.push_back(std::move(module));
  }

  SpaceshipCore::SpaceshipCore() :
    PhysicsObject(std::make_unique<CappedTransform>(100000, 15)) {}

  void SpaceshipCore::resetState() {
    physics::PhysicsObject::resetTransform();
    PhysicsObject::setAngle(util::degrees(-90));
  }

}
