#include "controls/player_input.hpp"

namespace controls {
  PlayerInput::PlayerInput(bool left, bool right, bool ahead)
  :
  left(left),
  right(right),
  ahead(ahead) {}

  PlayerInput getInput(std::queue<std::optional<sf::Event>>& events) {
    while(!events.empty()) {
      events.pop();
    }

    PlayerInput player_input;
    
    player_input.ahead = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    player_input.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    player_input.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    
    return player_input;
  }
}
