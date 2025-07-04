#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "parts/cores/spaceship_core.hpp"
#include "controls/controllers/controller.hpp"

namespace core {

  class Battle {
  private:
    sf::RenderWindow& window;
    std::vector<
      std::pair<
        parts::SpaceshipCore,
        controls::Controller
      >> cores;
  public:
    Battle(sf::RenderWindow& window);
    virtual void start();
  };

}

#endif
