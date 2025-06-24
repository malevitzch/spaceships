#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include <SFML/Graphics.hpp>

namespace physics {
  class PhysicsObject {
  private:
  public:
    virtual void addForce(double value, sf::Angle angle) = 0;
  };
}

#endif
