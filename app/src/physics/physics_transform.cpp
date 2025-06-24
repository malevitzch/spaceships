#include <numbers>
#include <cmath>

#include "physics/physics_transform.hpp"

namespace physics {
  sf::Vector2<double> PhysicsTransform::getPosition() {
    return position;
  }
  sf::Vector2<double> PhysicsTransform::getVelocity() {
    return velocity;
  }
  sf::Vector2<double> PhysicsTransform::getAcceleration() {
    return acceleration;
  }
  double PhysicsTransform::getAngle() {
    return angle;
  }
  double PhysicsTransform::getAngularVelocity() {
    return angular_velocity;
  }
  double PhysicsTransform::getAngularAcceleration() {
    return angular_acceleration;
  }
  void PhysicsTransform::update(double dt) {
    position += velocity * dt + (acceleration * (dt * dt)) / 2.0;
    velocity += acceleration * dt;

    angle = std::fmod(
      (angle + angular_velocity * dt + (angular_acceleration * (dt * dt)) / 2.0), 
      (2 * std::numbers::pi));
    angular_velocity += angular_acceleration * dt;
  }
}
