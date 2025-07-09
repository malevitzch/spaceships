#include "core/menu.hpp"
#include "parts/cores.hpp"
#include "parts/cores/omni_core.hpp"
#include "parts/cores/spaceship_core.hpp"
#include "utility/vec2d.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace core {
  Menu::Menu(sf::RenderWindow& window) : window(window) {
    ships.push_back(std::make_shared<parts::SimpleCore>());
    ships.push_back(std::make_shared<parts::OmniCore>());
  }
  std::shared_ptr<parts::SpaceshipCore> Menu::pickShip() {
    std::shared_ptr<parts::SpaceshipCore> ship = nullptr;
    sf::RectangleShape selections[3];
    for(int i = 0; i < 3; i++) {
      selections[i] = sf::RectangleShape();
      auto& rect = selections[i];
      rect.setOrigin({50, 50});
      rect.setSize({100, 100});
      //rect.setPosition(util::Vec2d(500, 500) + (i - 1) * 200);
    }
    while(window.isOpen() && ship == nullptr) {
      while(const std::optional event = window.pollEvent()) {
        if(event->is<sf::Event::Closed>()) {
          window.close();
        } else if(event->is<sf::Event::KeyPressed>()) {
          //TODO: implement
        }
      }

    }
    return ship;
  }
}
