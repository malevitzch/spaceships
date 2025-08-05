#ifndef CORE_SHIP_ACTOR_HPP
#define CORE_SHIP_ACTOR_HPP

#include <SFML/Graphics.hpp>
#include "controls/controllers/controller.hpp"
#include "parts/cores/spaceship_core.hpp"
#include "core/ship.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <memory>


namespace core {

  class ShipActor {
  private:
    std::shared_ptr<Ship> ship;
    std::shared_ptr<controls::Controller> controller;
  public:
    ShipActor(
      std::shared_ptr<Ship> core,
      std::shared_ptr<controls::Controller> controller);

    void makeDecisions();
    void physicsTick(double dt);

    Ship& getShip();
    std::shared_ptr<Ship> getShipPointer();
    controls::Controller& getController();

  };
}

#endif
