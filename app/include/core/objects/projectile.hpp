#ifndef CORE_OBJECTS_PROJECTILE_HPP
#define CORE_OBJECTS_PROJECTILE_HPP

#include "core/objects/space_object.hpp"

namespace core {
  class Projectile : public SpaceObject {
  private:
  public:
    // Inherits PhysicsTick from SpaceObject
    virtual bool isDestroyed() override = 0;
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override = 0;
  };
}

#endif
