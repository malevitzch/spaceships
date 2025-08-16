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

  void PlayerController::addMouseEvents(ShipOrders& orders) const {
    orders.mouse_left =
      sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    orders.mouse_right =
      sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
    orders.mouse_middle =
      sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
  }

  ShipOrders PlayerController::getOrders() {
    ShipOrders orders;
    addHolddownKeys(orders);
    setTarget(orders);
    addMouseEvents(orders);

    while(!events.empty()) {
      sf::Event event = events.front();
      if(const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        switch(keyPressed->scancode) {
          using sf::Keyboard::Scancode;
        case Scancode::Space:
          orders.space_p++;
          break;
        case Scancode::Num0:
          orders.actions[0]++;
          break;
        case Scancode::Num1:
          orders.actions[1]++;
          break;
        case Scancode::Num2:
          orders.actions[2]++;
          break;
        case Scancode::Num3:
          orders.actions[3]++;
          break;
        case Scancode::Num4:
          orders.actions[4]++;
          break;
        case Scancode::Num5:
          orders.actions[5]++;
          break;
        case Scancode::Num6:
          orders.actions[6]++;
          break;
        case Scancode::Num7:
          orders.actions[7]++;
          break;
        case Scancode::Num8:
          orders.actions[8]++;
          break;
        case Scancode::Num9:
          orders.actions[9]++;
          break;

        default:
          break;
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
