#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "physics_transform.hpp"

#include <SFML/Graphics.hpp>

namespace physics {
  class PhysicsObject {
  private:
  protected:
    PhysicsTransform transform;
  public:
    PhysicsObject(PhysicsTransform transform);
    virtual void physicsTick(double dt) = 0;

    util::Vec2d getPosition() const;
    void setPosition(util::Vec2d target);

    util::Vec2d getVelocity() const;
    void setVelocity(util::Vec2d target);

    util::Vec2d getAcceleration() const;
    void setAcceleration(util::Vec2d target);

    util::Angle getAngle() const;
    void setAngle(util::Angle angle);

    double getAngularVelocity() const;
    void setAngularVelocity(util::Angle angle);

    double getAngularAcceleration() const;
    void setAngularAcceleration(util::Angle angle);
  };
}

#endif
