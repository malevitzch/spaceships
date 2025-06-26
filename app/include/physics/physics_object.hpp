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
    virtual void physicsTick(double dt) = 0;
  };
}

#endif
