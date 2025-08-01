#include "parts/cores/simple_core.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Angle.hpp>
#include <cmath>

#include "assets/texture_manager.hpp"
#include "physics/physics_object.hpp"
#include "utility/normalizer.hpp"

namespace parts {
  SimpleCore::SimpleCore() : SpaceshipCore(100, 100) {}
  SimpleCore::SimpleCore(double thrust, double angular_thrust) 
    : SpaceshipCore(100, 100),
      thrust(thrust),
      angular_thrust(angular_thrust) {}
  void SimpleCore::physicsTick(double dt) {
    // We first add the thrust to the transform (if engines are on),
    // then we compute the physics tick
    // And finally we subtract it back
    util::Vec2d acceleration = {0, 0};
    if(engines_on) {
      acceleration =
        {(float)(thrust * cos(getTransform().angle)),
        (float)(thrust * sin(getTransform().angle))};
    }

    // Add the thrust to the transform so that its taken into account
    getTransform().acceleration += acceleration;
    getTransform().angular_acceleration += angular_thrust * angular_engines;

    PhysicsObject::physicsTick(dt);

    // Subtract back the thrust
    // This is much more convenient than keeping an ON/OFF meter since the meter
    // Would have to somehow be a part of the transform
    getTransform().acceleration -= acceleration;
    getTransform().angular_acceleration -= angular_thrust * angular_engines;
  }

  std::vector<std::shared_ptr<Part>> SimpleCore::getChildren() {
    return {};
  }
  void SimpleCore::handleInstructions(controls::ShipOrders input) {
    if(input.ahead) {
      turnOnEngines();
    } else {
      turnOffEngines();
    }
    // Pressing both buttons at once makes the ship try to stablize rotation
    if(input.left && input.right) {
      util::normalize(
        *this,
        static_cast<double (SimpleCore::*)() const>(
          &PhysicsObject::getAngularVelocity),
        &SimpleCore::angularRight,
        &SimpleCore::angularLeft,
        &SimpleCore::angularOff);
    } else if(input.left) {
      angularLeft();
    } else if(input.right) {
      angularRight();
    } else {
      angularOff();
    }
  }

  void SimpleCore::turnOnEngines() {
    engines_on = true;
  }
  void SimpleCore::turnOffEngines() {
    engines_on = false;
  }

  void SimpleCore::angularLeft() {
    angular_engines = -1;
  }
  void SimpleCore::angularRight() {
    angular_engines = 1;
  }
  void SimpleCore::angularOff() {
    angular_engines = 0;
  }

}
