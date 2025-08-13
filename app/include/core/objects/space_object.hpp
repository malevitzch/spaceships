#ifndef CORE_OBJECTS_SPACE_OBJECT_HPP
#define CORE_OBJECTS_SPACE_OBJECT_HPP

#include "physics/physics_object.hpp"
#include <SFML/Graphics/Drawable.hpp>
namespace core {
  class SpaceObject : public physics::PhysicsObject, public sf::Drawable {
  private:
  protected:
  public:
    SpaceObject();
    virtual bool isDestroyed() = 0;
  };
}

#endif
