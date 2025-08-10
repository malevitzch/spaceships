#ifndef CORE_OBJECTS_SPACE_OBJECT_HPP
#define CORE_OBJECTS_SPACE_OBJECT_HPP

#include "physics/physics_object.hpp"
namespace core {
  class SpaceObject : physics::PhysicsObject {
  private:
  public:
    SpaceObject();
    virtual bool isDestroyed() = 0;
  };
}

#endif
