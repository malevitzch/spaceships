#include "core/ship_actor.hpp"
#include "assets/texture_manager.hpp"
#include "controls/ship_orders.hpp"

namespace core {
  ShipActor::ShipActor(
    std::shared_ptr<Ship> ship,
    std::shared_ptr<controls::Controller> controller,
    std::string texture_name)
  :
    ship(ship),
    controller(controller) {}

  void ShipActor::makeDecisions() {
    controls::ShipOrders orders = controller->getOrders();
    ship->getCore().handleInstructions(orders);
  }

  void ShipActor::physicsTick(double dt) {
    ship->getCore().physicsTick(dt);
  }

}
