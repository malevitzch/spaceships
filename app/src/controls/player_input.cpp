#include "controls/player_input.hpp"

namespace controls {
  PlayerInput::PlayerInput(bool left, bool right, bool ahead, bool back)
  :
  left(left),
  right(right),
  ahead(ahead),
  back(back) {}

  PlayerInput getInput(std::queue<std::optional<sf::Event>>& events) {
    while(!events.empty()) {
      events.pop();
    }

    PlayerInput player_input;

    player_input.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    player_input.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    player_input.ahead = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    player_input.back = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);

    player_input.left_arrow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    player_input.right_arrow = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);

    return player_input;
  }
}
