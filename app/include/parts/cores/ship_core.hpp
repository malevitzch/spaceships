#ifndef PARTS_CORES_SHIP_CORE_HPP
#define PARTS_CORES_SHIP_CORE_HPP

#include "parts/modules/trigger_module.hpp"

#include "physics/physics_object.hpp"

#include "controls/ship_orders.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace core {
  class Battle;
}

namespace parts {
  class ShipCore :
    public physics::PhysicsObject {
  private:
  protected:
    //TODO: this can honestly even be private later
    std::vector<std::unique_ptr<TriggerModule>> trigger_modules;
    void broadcastSignal(int code);
    void broadcastSignal(int code, std::vector<std::string> args);
    void broadcastSignal(Signal signal);

    core::Battle* battle;
  public:
    ShipCore();

    //FIXME: this should allow for some nicer argument passing
    // and not require the creation of unique_ptr to the object
    void addTriggerModule(std::unique_ptr<TriggerModule> module);

    // Any override of this function should call the parent version
    // in 99.9% of situations
    virtual void resetState();

    virtual void handleInstructions(controls::ShipOrders input) = 0;

    void setBattle(core::Battle* battle);
    core::Battle& getBattle();
  };
}

#endif
