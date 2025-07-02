#ifndef PLAYER_INPUT_HPP
#define PLAYER_INPUT_HPP

#include <SFML/Graphics.hpp>

#include <queue>

namespace controls {
  // Struct that contains extracted information
  // from what the player pressed
  struct PlayerInput {
    bool left = false;
    bool right = false;

    bool ahead = false;

    PlayerInput() = default;
    PlayerInput(bool left, bool right, bool ahead);
  };

  PlayerInput getInput(std::queue<std::optional<sf::Event>>& events);
}

#endif
