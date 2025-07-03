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
    bool back = false;

    bool left_arrow = false;
    bool right_arrow = false;

    PlayerInput() = default;
    PlayerInput(bool left, bool right, bool ahead, bool back);
  };

  PlayerInput getInput(std::queue<std::optional<sf::Event>>& events);
}

#endif
