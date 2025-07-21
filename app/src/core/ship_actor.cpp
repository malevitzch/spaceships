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
    controller(controller),
    sprite(*assets::TextureManager::getShipTexture(texture_name)) {
    sprite.setOrigin({25, 25});
  }

  void ShipActor::makeDecisions() {
    controls::ShipOrders orders = controller->getOrders();
    ship->getCore().handleInstructions(orders);
  }

  void ShipActor::physicsTick(double dt) {
    ship->getCore().physicsTick(dt);
  }

  void ShipActor::draw(
    sf::RenderTarget& target,
    sf::RenderStates states) const {
    //FIXME: this part is going to be replaced by calculation of on-screen
    // position out of the logical position that the ship holds
    states.transform.translate(ship->getCore().getPosition());
    states.transform.rotate(sf::radians(ship->getCore().getAngle()));

    target.draw(*ship, states);
  }
}
