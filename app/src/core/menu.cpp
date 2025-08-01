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

    ships.push_back(std::make_shared<Ship>(
      "Bug Mk. 1",
      std::make_shared<parts::SimpleCore>(),
      "Bug"));

    ships.push_back(std::make_shared<Ship>(
      "Phage Mk. 1",
      std::make_shared<parts::SimpleCore>(5000, 4),
      "Phage"));
  }
  std::shared_ptr<Ship> Menu::pickShip() {
    std::shared_ptr<sf::Font> font = assets::FontManager::getFont("orbitron");
    std::shared_ptr<Ship> ship = nullptr;
    for(auto& ship : ships) {
      ship->getCore().resetState();
      ship->getCore().setAngle(util::degrees(-90));
    }

    constexpr int SELECTIONS_COUNT = 3;
    constexpr int CENTER = SELECTIONS_COUNT / 2;

    const Vec2d REGULAR_SIZE = {60.0, 60.0};
    const Vec2d CENTER_SIZE = {90.0, 90.0};

    //FIXME: selections should probably just hold a struct or smth
    sf::RectangleShape selections[3];
    for(int i = 0; i < 3; i++) {
      selections[i] = sf::RectangleShape();
      auto& rect = selections[i];
      rect.setOrigin({50, 50});
      rect.setSize({100, 100});
      rect.setPosition(Vec2d(500, 500) + (i - 1) * Vec2d(150, 0));
    }
    selections[CENTER].setOrigin({60, 60});
    selections[CENTER].setSize({120, 120});
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

        auto ship_sprite = ship.getSprite().getImageSprite();

        if(i == CENTER) {
          Vec2d size = ship_sprite.getGlobalBounds().size;
          ship_sprite.scale(Vec2d( CENTER_SIZE.x / size.x, CENTER_SIZE.y / size.y));
        } else {
          Vec2d size = ship_sprite.getGlobalBounds().size;
          ship_sprite.scale(Vec2d( REGULAR_SIZE.x / size.x, REGULAR_SIZE.y / size.y));
        }

        window.draw(ship_sprite, states);
      }
      window.display();
    }
    return ship;
  }
}
