#ifndef SPACESHIP_CORE_HPP
#define SPACESHIP_CORE_HPP

#include "parts/modules/trigger_module.hpp"

#include "physics/physics_object.hpp"

#include "controls/ship_orders.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace parts {
  class SpaceshipCore :
    public physics::PhysicsObject {
  private:
  protected:
    //TODO: this can honestly even be private later
    std::vector<std::unique_ptr<TriggerModule>> trigger_modules;
    void broadcastSignal(int code);
    void broadcastSignal(int code, std::vector<std::string> args);
    void broadcastSignal(Signal signal);

    //FIXME: this should allow for some nicer argument passing
    // and not require the creation of unique_ptr to the object
    void addTriggerModule(std::unique_ptr<TriggerModule> module);
  public:
    SpaceshipCore();

    // Any override of this function should call the parent version
    // in 99.9% of situations
    virtual void resetState();

    virtual void handleInstructions(controls::ShipOrders input) = 0;
  };
}

#endif
