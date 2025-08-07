#ifndef SPACESHIP_CORE_HPP
#define SPACESHIP_CORE_HPP

#include "parts/modules/module.hpp"

#include "physics/physics_object.hpp"

#include "controls/ship_orders.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace parts {
  class SpaceshipCore :
    public physics::PhysicsObject {
  private:
  protected:
  public:
    SpaceshipCore();

    // Any override of this function should call the parent version
    // in 99.9% of situations
    virtual void resetState();

    virtual void handleInstructions(controls::ShipOrders input) = 0;
  };
}

#endif
