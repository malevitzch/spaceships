#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "parts/cores/spaceship_core.hpp"

namespace core {

  class Battle {
  private:
    sf::RenderWindow& window;
    //FIXME: this contains pairs of controller, core
    // Controller is always prompted for instructions
    // And the core accepts instructions
    std::vector<parts::SpaceshipCore> cores;
  public:
    Battle(sf::RenderWindow& window);

    virtual void start();
  };

}

#endif
