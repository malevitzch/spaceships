#include "core/menu.hpp"
#include "parts/cores.hpp"
#include "parts/cores/omni_core.hpp"
#include "parts/cores/spaceship_core.hpp"
#include "utility/angle.hpp"
#include "utility/vec2d.hpp"
#include "assets/font_manager.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace core {
  using util::Vec2d;
  Menu::Menu(sf::RenderWindow& window) : window(window) {
    ships.push_back(std::make_shared<Ship>(
      "Bird Mk. 1",
      std::make_shared<parts::SimpleCore>(),
      "Bird"));

    ships.push_back(std::make_shared<Ship>(
      "Borg Mk. 1",
      std::make_shared<parts::OmniCore>(5000, 3000, 5000),
      "BorgMk1"));

    ships.push_back(std::make_shared<Ship>(
      "Borg Mk. 2",
      std::make_shared<parts::OmniCore>(7000, 5000, 3000),
      "BorgMk2"));

    ships.push_back(std::make_shared<Ship>(
      "Round",
      std::make_shared<parts::OmniCore>(7000, 7000, 7000),
      "Round"));
  }
  std::shared_ptr<Ship> Menu::pickShip() {
    std::shared_ptr<sf::Font> font = assets::FontManager::getFont("orbitron");
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
      rect.setPosition(Vec2d(500, 500) + (i - 1) * Vec2d(150, 0));
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
              (ships.size() + selection_index + 1) % ships.size();
          } else if(keyPressed->scancode == sf::Keyboard::Scancode::D) {
            selection_index =
              (ships.size() + selection_index - 1) % ships.size();
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
          *ships[(i - selection_index + ships.size() - 1) % ships.size()];
        Vec2d pos = {500.0 + (i - 1) * 150, 500};

        Vec2d text_pos = pos - Vec2d(0, -55);
        sf::Text name(*font);

        name.setOrigin({50, 0});
        name.setCharacterSize(20);
        if(i == 1) {
          text_pos.y += 10;
          name.setCharacterSize(25);
          name.setOrigin({60, 0});
        }

        name.setString(ship.getName());
        name.setPosition(text_pos);

        window.draw(name);

        sf::RenderStates states;
        states.transform.translate(pos);
        states.transform.rotate(sf::degrees(-90));
        window.draw(ship, states);
      }
      window.display();
    }
    return ship;
  }
}
