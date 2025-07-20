#include "controls/controllers/player_controller.hpp"

namespace controls {
  void PlayerController::addHolddownKeys(ShipOrders& orders) const {
    orders.left =
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    orders.right =
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    orders.ahead =
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    orders.back =
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);

    orders.left_arrow =
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    orders.right_arrow =
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
  }
  ShipOrders PlayerController::getOrders() {
    ShipOrders orders;
    addHolddownKeys(orders);

    while(!events.empty()) {
      // FIXME: events are currently being ignored
      // but only because player clicks don't mean anything yet`
      events.pop();
    }

    return orders;
  }
  void PlayerController::addEvent(sf::Event event) {
    events.push(event);
  }
}
