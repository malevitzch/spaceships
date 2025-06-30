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

    void setPosition(util::Vec2d target);
  };
}

#endif
