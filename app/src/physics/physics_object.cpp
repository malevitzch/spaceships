#include "physics/physics_object.hpp"

namespace physics {
  PhysicsObject::PhysicsObject(PhysicsTransform transform) : transform(transform) {}

  util::Vec2d PhysicsObject::getPosition() const {
    return transform.position;
  }
  void PhysicsObject::setPosition(util::Vec2d target) {
    this->transform.position = target;
  }

  util::Vec2d PhysicsObject::getVelocity() const {
    return transform.velocity;
  }
  void PhysicsObject::setVelocity(util::Vec2d velocity) {
    this->transform.velocity = velocity;
  }

  util::Vec2d PhysicsObject::getAcceleration() const {
    return transform.position;
  }
  void PhysicsObject::setAcceleration(util::Vec2d acceleration) {
    this->transform.acceleration = acceleration;
  }

  util::Angle PhysicsObject::getAngle() const {
    return transform.angle;
  }
  void PhysicsObject::setAngle(util::Angle angle) {
    transform.angle = angle;
  }

  util::Angle PhysicsObject::getAngularVelocity() const {
    return transform.angular_velocity;
  }
  void PhysicsObject::setAngularVelocity(util::Angle angular_velocity) {
    transform.angular_velocity = angular_velocity;
  }

  util::Angle PhysicsObject::getAngularAcceleration() const {
    return transform.angular_acceleration;
  }
  void PhysicsObject::setAngularAcceleration(util::Angle angular_acceleration) {
    transform.angular_acceleration = angular_acceleration;
  }
}
