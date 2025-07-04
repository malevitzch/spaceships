#include <numbers>
#include <cmath>

#include "physics/physics_transform.hpp"

namespace physics {
  PhysicsTransform::PhysicsTransform(
    util::Vec2d position,
    util::Vec2d velocity,
    util::Vec2d acceleration,
    util::Angle angle,
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
    // TODO: make position not directly linked to the pixel position on the 
    // display
    position += (velocity * dt + (acceleration * (dt * dt)) / 2.0) / 100.0;
    velocity += acceleration * dt;

    angle += (angular_velocity * dt + (angular_acceleration * (dt * dt)) / 2.0);
    angular_velocity += angular_acceleration * dt;
  }

  CappedTransform::CappedTransform(
    util::Vec2d position,
    util::Vec2d velocity,
    util::Vec2d acceleration,
    util::Angle angle,
    double angular_velocity,
    double angular_acceleration,
    double velocity_cap,
    double angular_velocity_cap) 
  :
  PhysicsTransform(
    position,
    velocity,
    acceleration,
    angle,
    angular_velocity,
    angular_acceleration),
  velocity_cap(velocity_cap),
  angular_velocity_cap(angular_velocity_cap) {
  }
  CappedTransform::CappedTransform(
    double velocity_cap,
    double angular_velocity_cap)
  :
  physics::PhysicsTransform(),
  velocity_cap(velocity_cap),
  angular_velocity_cap(angular_velocity_cap) {
  }
  void CappedTransform::tick(double dt) {
    PhysicsTransform::tick(dt);
    if(velocity.magnitude() >= velocity_cap) {
      velocity.rescale(velocity_cap);
    }
    if(std::fabs(angular_velocity) >= angular_velocity_cap) {
      angular_velocity = angular_velocity_cap * (angular_velocity < 0 ? -1 : 1);
    }
  }

}
