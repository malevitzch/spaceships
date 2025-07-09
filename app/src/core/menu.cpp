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
    ships.push_back(std::make_shared<parts::OmniCore>());
  }
  std::shared_ptr<parts::SpaceshipCore> Menu::pickShip() {
    std::shared_ptr<parts::SpaceshipCore> ship = nullptr;

    //FIXME: selections should probably just hold a struct or smth
    sf::RectangleShape selections[3];
    for(int i = 0; i < 3; i++) {
      selections[i] = sf::RectangleShape();
      auto& rect = selections[i];
      rect.setOrigin({50, 50});
      rect.setSize({100, 100});
      rect.setPosition(util::Vec2d(500, 500) + (i - 1) * util::Vec2d(150, 0));
    }
    selections[1].setOrigin({60, 60});
    selections[1].setSize({120, 120});
    while(window.isOpen() && ship == nullptr) {
      while(const std::optional event = window.pollEvent()) {
        if(event->is<sf::Event::Closed>()) {
          window.close();
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
          if(keyPressed->scancode == sf::Keyboard::Scancode::A) {
            selection_index = (ships.size() + selection_index - 1) % ships.size();
          } else if(keyPressed->scancode == sf::Keyboard::Scancode::D) {
            selection_index = (ships.size() + selection_index + 1) % ships.size();
          } else if(keyPressed->scancode == sf::Keyboard::Scancode::Space) {
            return ships[(ships.size() - selection_index) % ships.size()];
          }
        }
      }
      window.clear();
      for(int i = 0; i < 3; i++) {
        window.draw(selections[i]);
        auto& ship = ships[(i - selection_index + ships.size() - 1) % ships.size()];
        ship->setPosition(util::Vec2d(500, 500) + (i - 1) * util::Vec2d(150, 0));
        window.draw(*ship);
      }
      window.display();
    }
    return ship;
  }
}
