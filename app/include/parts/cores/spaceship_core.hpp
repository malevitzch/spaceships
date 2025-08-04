#ifndef SPACESHIP_CORE_HPP
#define SPACESHIP_CORE_HPP

#include "physics/physics_object.hpp"

#include "controls/ship_orders.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace parts {
  class SpaceshipCore :
    public physics::PhysicsObject {
  private:
    int hp;
    int mass;
  protected:
  public:
    SpaceshipCore(int hp, int mass);

    // Any override of this function should call the super
    virtual void resetState();

    virtual void handleInstructions(controls::ShipOrders input) = 0;
  };
}

#endif
