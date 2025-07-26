#include "controls/controllers/player_controller.hpp"
#include "core/game.hpp"

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
  void PlayerController::setTarget(ShipOrders& orders) const {
    util::Vec2d mouse_pos = sf::Mouse::getPosition(battle->getWindow());
    orders.target = battle->getCamera().inverseTranslatePosition(mouse_pos);
  }
  ShipOrders PlayerController::getOrders() {
    ShipOrders orders;
    addHolddownKeys(orders);
    setTarget(orders);

    while(!events.empty()) {
      sf::Event event = events.front();
      if(const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if(keyPressed->scancode == sf::Keyboard::Scancode::Space) {
          orders.space++;
        }
      }
      events.pop();
    }

    return orders;
  }
  void PlayerController::addEvent(sf::Event event) {
    events.push(event);
  }
}
