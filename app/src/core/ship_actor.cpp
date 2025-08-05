#include "core/ship_actor.hpp"
#include "assets/texture_manager.hpp"
#include "controls/ship_orders.hpp"

namespace core {
  ShipActor::ShipActor(std::shared_ptr<Ship> ship,
                       std::shared_ptr<controls::Controller> controller) :
      ship(ship),
      controller(controller) {}

  void ShipActor::makeDecisions() {
    controls::ShipOrders orders = controller->getOrders();
    ship->getCore().handleInstructions(orders);
  }

  void ShipActor::physicsTick(double dt) {
    ship->getCore().physicsTick(dt);
  }

  Ship& ShipActor::getShip() { return *ship; }
  std::shared_ptr<Ship> ShipActor::getShipPointer() { return ship; }
  controls::Controller& ShipActor::getController() { return *controller; }

}
