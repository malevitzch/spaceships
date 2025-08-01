#include <algorithm>
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

    PhysicsTransform PhysicsTransform::operator+(
      const PhysicsTransform& transform) const {
      PhysicsTransform result(*this);
      result += transform;
      return result;
    }
    PhysicsTransform& PhysicsTransform::operator+=(
      const PhysicsTransform& transform) {

      position += transform.position;
      velocity += transform.velocity;
      acceleration += transform.acceleration;

      angle += transform.angle;
      angular_velocity += transform.angular_velocity;
      angular_acceleration += transform.angular_acceleration;

      return *this;
    }

    PhysicsTransform PhysicsTransform::operator-(
      const PhysicsTransform& transform) const {
      PhysicsTransform result(*this);
      result -= transform;
      return result;
    }
    PhysicsTransform& PhysicsTransform::operator-=(
      const PhysicsTransform& transform) {

      position -= transform.position;
      velocity -= transform.velocity;
      acceleration -= transform.acceleration;

      angle -= transform.angle;
      angular_velocity -= transform.angular_velocity;
      angular_acceleration -= transform.angular_acceleration;

      return *this;
    }

  void PhysicsTransform::tick(double dt) {
    position += (velocity * dt + (acceleration * (dt * dt)) / 2.0) / 100.0;
    velocity += acceleration * dt;

    angle += (angular_velocity * dt + (angular_acceleration * (dt * dt)) / 2.0);
    angular_velocity += angular_acceleration * dt;
  }
  void PhysicsTransform::tick(double dt, std::vector<PhysicsTransform> transforms) {
    for(PhysicsTransform transform : transforms) {
      *this += transform;
    }
    tick(dt);
    for(PhysicsTransform transform : transforms) {
      *this -= transform;
    }
  }

  void PhysicsTransform::reset() {
    position = {0, 0};
    velocity = {0, 0};
    acceleration = {0, 0};

    angle = 0;
    angular_velocity = 0;
    angular_acceleration = 0;
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
    if(velocity.magnitude() >= velocity_cap) {
      velocity.rescale(velocity_cap);
    }
    angular_velocity = std::clamp(
      angular_velocity,
      -angular_velocity_cap,
      angular_velocity_cap);
    PhysicsTransform::tick(dt);
  }

}
