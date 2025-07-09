#ifndef CORE_MENU_HPP
#define CORE_MENU_HPP

#include "parts/cores/spaceship_core.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
namespace core {
  class Menu {
  private:
    sf::RenderWindow& window;
    std::vector<std::shared_ptr<parts::SpaceshipCore>> ships;
    int selection_index = 0;
  public:
    Menu(sf::RenderWindow& window);
    // Returns a pointer to the ship's core, null otherwise
    // (if the menu was exited in a different way than by picking a ship)
    std::shared_ptr<parts::SpaceshipCore> pickShip();
  };
}

#endif
