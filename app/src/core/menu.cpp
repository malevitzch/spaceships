#include "core/menu.hpp"
#include "parts/cores.hpp"
#include "parts/cores/omni_core.hpp"
#include "parts/cores/spaceship_core.hpp"
#include "utility/angle.hpp"
#include "utility/vec2d.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace core {
  Menu::Menu(sf::RenderWindow& window) : window(window) {
    ships.push_back(std::make_shared<Ship>(
      "Bird Mk. 1",
      std::make_shared<parts::SimpleCore>(),
      "BasicShip"));
    ships.push_back(std::make_shared<Ship>(
      "Borg Mk. 1",
      std::make_shared<parts::OmniCore>(),
      "OmniShip"));
    ships.push_back(std::make_shared<Ship>(
      "Borg Mk. 2",
      std::make_shared<parts::OmniCore>(),
      "OmniShip"));
    //ships.push_back(std::make_shared<parts::OmniCore>());
    //ships.push_back(std::make_shared<parts::OmniCore>());
  }
  std::shared_ptr<Ship> Menu::pickShip() {
    std::shared_ptr<Ship> ship = nullptr;
    for(auto& ship : ships) {
      ship->getCore().resetTransform();
      ship->getCore().setAngle(util::degrees(-90));
    }
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
        // Keys A-D are used to move the selection left or right
        // And Space/Enter is used to select the ship currently in the middle 
        if(event->is<sf::Event::Closed>()) {
          window.close();
        } else if (
          const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
          if(keyPressed->scancode == sf::Keyboard::Scancode::A) {
            selection_index =
              (ships.size() + selection_index - 1) % ships.size();
          } else if(keyPressed->scancode == sf::Keyboard::Scancode::D) {
            selection_index =
              (ships.size() + selection_index + 1) % ships.size();
          } else if(keyPressed->scancode == sf::Keyboard::Scancode::Space
                    || keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
            return ships[(ships.size() - selection_index) % ships.size()];
          }
        }
      }
      window.clear();
      for(int i = 0; i < 3; i++) {
        window.draw(selections[i]);
        auto& ship =
          ships[(i - selection_index + ships.size() - 1) % ships.size()];
        ship->getCore().setPosition(
          util::Vec2d(500, 500) + (i - 1) * util::Vec2d(150, 0));
        sf::RenderStates states;
        states.transform.translate(ship->getCore().getPosition());
        states.transform.rotate(sf::radians(ship->getCore().getAngle()));
        window.draw(*ship, states);
      }
      window.display();
    }
    return ship;
  }
}
