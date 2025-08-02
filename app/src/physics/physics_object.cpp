#include "physics/physics_object.hpp"

namespace physics {
  PhysicsObject::PhysicsObject(std::unique_ptr<PhysicsTransform> transform)
  : transform(std::move(transform)) {}

  void PhysicsObject::physicsTick(double dt) {
    getTransform().tick(dt);
  }
  void PhysicsObject::physicsTick(double dt, std::vector<PhysicsTransform> transforms) {
    getTransform().tick(dt, transforms);
  }

  util::Vec2d PhysicsObject::getPosition() const {
    return transform->position;
  }
  double PhysicsObject::getPositionX() const {
    return getPosition().x;
  }
  double PhysicsObject::getPositionY() const {
    return getPosition().y;
  }
  void PhysicsObject::setPosition(util::Vec2d target) {
    getTransform().position = target;
  }

  util::Vec2d PhysicsObject::getVelocity() const {
    return transform->velocity;
  }
  double PhysicsObject::getVelocityX() const {
    return getVelocity().x;
  }
  double PhysicsObject::getVelocityY() const {
    return getVelocity().y;
  }
  void PhysicsObject::setVelocity(util::Vec2d velocity) {
    transform->velocity = velocity;
  }

  util::Vec2d PhysicsObject::getAcceleration() const {
    return transform->position;
  }
  double PhysicsObject::getAccelerationX() const {
    return getAcceleration().x;
  }
  double PhysicsObject::getAccelerationY() const {
    return getAcceleration().y;
  }
  void PhysicsObject::setAcceleration(util::Vec2d acceleration) {
    transform->acceleration = acceleration;
  }

  util::Angle PhysicsObject::getAngle() const {
    return transform->angle;
  }
  void PhysicsObject::setAngle(util::Angle angle) {
    transform->angle = angle;
  }

  double PhysicsObject::getAngularVelocity() const {
    return transform->angular_velocity;
  }
  void PhysicsObject::setAngularVelocity(util::Angle angular_velocity) {
    transform->angular_velocity = angular_velocity;
  }

  double PhysicsObject::getAngularAcceleration() const {
    return transform->angular_acceleration;
  }
  void PhysicsObject::setAngularAcceleration(util::Angle angular_acceleration) {
    transform->angular_acceleration = angular_acceleration;
  }

  void PhysicsObject::resetTransform() {
    transform->reset();
  }

  PhysicsTransform& PhysicsObject::getTransform() {
    return *transform;
  }
}
