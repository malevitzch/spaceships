#include <numbers>
#include <cmath>

#include "physics/physics_transform.hpp"

namespace physics {
  PhysicsTransform::PhysicsTransform(
    sf::Vector2<double> position,
    sf::Vector2<double> velocity,
    sf::Vector2<double> acceleration,
    double angle,
    double angular_velocity,
    double angular_acceleration) 
    :
    position(position),
    velocity(velocity),
    acceleration(acceleration),
    angle(angle),
    angular_velocity(angular_velocity),
    angular_acceleration(angular_acceleration) {}

  void PhysicsTransform::tick(double dt) {
    position += (velocity * dt + (acceleration * (dt * dt)) / 2.0) / 100.0;
    velocity += acceleration * dt;

    angle = std::fmod(
      (angle + (angular_velocity * dt + (angular_acceleration * (dt * dt)) / 2.0) / 100.0), 
      (2 * std::numbers::pi));
    angular_velocity += angular_acceleration * dt;
  }
}
