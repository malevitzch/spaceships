#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include "physics_transform.hpp"

#include <SFML/Graphics.hpp>

namespace physics {
  class PhysicsObject {
  private:
  protected:
    std::unique_ptr<PhysicsTransform> transform;
  public:
    PhysicsObject(std::unique_ptr<PhysicsTransform> transform);
    virtual void physicsTick(double dt);
    virtual void physicsTick(double dt, std::vector<PhysicsTransform> transforms);

    util::Vec2d getPosition() const;
    double getPositionX() const;
    double getPositionY() const;
    void setPosition(util::Vec2d target);

    util::Vec2d getVelocity() const;
    double getVelocityX() const;
    double getVelocityY() const;
    void setVelocity(util::Vec2d target);

    util::Vec2d getAcceleration() const;
    double getAccelerationX() const;
    double getAccelerationY() const;
    void setAcceleration(util::Vec2d target);

    util::Angle getAngle() const;
    void setAngle(util::Angle angle);

    double getAngularVelocity() const;
    void setAngularVelocity(util::Angle angle);

    double getAngularAcceleration() const;
    void setAngularAcceleration(util::Angle angle);

    void resetTransform();

    PhysicsTransform& getTransform();
  };
}

#endif
