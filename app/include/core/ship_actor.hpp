#ifndef CORE_SHIP_ACTOR_HPP
#define CORE_SHIP_ACTOR_HPP

#include "controls/controllers/controller.hpp"
#include "core/ship.hpp"

#include <memory>


namespace core {

  class ShipActor {
  private:
    std::shared_ptr<Ship> ship;
    std::shared_ptr<controls::Controller> controller;

    //TODO: for now the default team is 1, team 0 
    // is for the "local" player
    // in the future teams might be a bit more complicated than just
    // a single integer but its ok for now
    int team = 1;
  public:
    ShipActor(
      std::shared_ptr<Ship> core,
      std::shared_ptr<controls::Controller> controller);

    void makeDecisions();
    void physicsTick(double dt);

    Ship& getShip();
    std::shared_ptr<Ship> getShipPointer();
    controls::Controller& getController();
    int getTeam() const;

    void setTeam(int team);

  };
}

#endif
