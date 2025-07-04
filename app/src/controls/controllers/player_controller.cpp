#include "controls/controllers/player_controller.hpp"

namespace controls {
  ShipOrders PlayerController::getOrders() {
    while(!events.empty()) {
      //FIXME: events are currently being ignored
      // but only because player clicks don't mean anything yet`
      events.pop();
    }

    ShipOrders player_input;

    player_input.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    player_input.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    player_input.ahead = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    player_input.back = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);

    player_input.left_arrow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    player_input.right_arrow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);

    return player_input;
  }
  void PlayerController::addEvent(sf::Event event) {
    events.push(event);
  }
}
