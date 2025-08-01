#ifndef SPACESHIP_CORE_HPP
#define SPACESHIP_CORE_HPP

#include "physics/physics_object.hpp"

#include "parts/part.hpp"

#include "controls/ship_orders.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace parts {
  class SpaceshipCore :
    public Part,
    public physics::PhysicsObject {
  private:
    int hp;
    int mass;
  protected:
  public:
    SpaceshipCore(int hp, int mass);

    // Any override of this function should call the super
    virtual void resetState();

    // TODO: this probably needs some other implementatoin
    virtual int getHp() override;
    virtual int getMass() override;

    // SpaceshipCore by itself does not implement things like getChildren()
    // because SpaceshipCore is still an abstract class

    virtual void handleInstructions(controls::ShipOrders input) = 0;
  };
}

#endif
