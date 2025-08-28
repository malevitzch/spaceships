#include "core/menu.hpp"
#include "assets/texture_manager.hpp"
#include "parts/cores.hpp"
#include "parts/modules/simple_weapon.hpp"
#include "parts/modules/velocity_redirector.hpp"
#include "utility/angle.hpp"
#include "utility/vec2d.hpp"
#include "assets/font_manager.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

#include "parts/modules/null_brake.hpp"

namespace core {
  using util::Vec2d;
  Menu::Menu(sf::RenderWindow& window) : window(window) {
    ships.push_back(std::make_shared<Ship>(
      "Bird Mk. 1",
      std::make_shared<parts::SimpleCore>(),
      "Bird"));

    ships.push_back(std::make_shared<Ship>(
      "Borg Mk. 1",
      std::make_shared<parts::OmniCore>(50, 30, 50),
      "BorgMk1"));

    ships.push_back(std::make_shared<Ship>(
      "Borg Mk. 2",
      std::make_shared<parts::OmniCore>(70, 50, 30),
      "BorgMk2"));

    ships.push_back(std::make_shared<Ship>(
      "Round",
      std::make_shared<parts::OmniCore>(70, 70, 70),
      "Round"));

    ships.push_back(std::make_shared<Ship>(
      "Bug Mk. 1",
      std::make_shared<parts::SimpleCore>(),
      "Bug"));

    ships.push_back(std::make_shared<Ship>(
      "Spore Mk. 1",
      std::make_shared<parts::MouseCore>(70, 0.5),
      "Spore"));

    ships.push_back(std::make_shared<Ship>(
      "Phage Mk. 1",
      std::make_shared<parts::SimpleCore>(50, 4),
      "Phage"));

    ships.push_back(std::make_shared<Ship>(
      "Phage Mk. 2",
      std::make_shared<parts::SimpleCore>(100, 6),
      "PhageMk2"));
    ships.back()->getCore().addTriggerModule(
      std::move(std::make_unique<parts::NullBrake>(1, 5)));
    ships.back()->getCore().addTriggerModule(
      std::move(std::make_unique<parts::VelocityRedirector>(2, 1, 0.7)));

    auto weapon = std::make_unique<parts::SimpleWeapon>(
      3,
      0.1,
      "RedLaserBolt",
      Vec2d(50, 0),
      util::Angle(0),
      750,
      5,
      0.1);
    ships.back()->getCore().addTriggerModule(std::move(weapon));
  }
  std::shared_ptr<Ship> Menu::pickShip() {
    std::shared_ptr<sf::Font> font = assets::FontManager::getFont("orbitron");
    std::shared_ptr<Ship> ship = nullptr;
    for(auto& ship : ships) {
      ship->getCore().resetState();
      ship->getCore().setAngle(util::degrees(-90));
    }

    constexpr int SELECTIONS_COUNT = 7;
    constexpr int CENTER = SELECTIONS_COUNT / 2;

    const Vec2d REGULAR_SIZE = {60.0, 60.0};
    const Vec2d CENTER_SIZE = {150.0, 150.0};

    const Vec2d SELECTION_SIZE = REGULAR_SIZE * 1.7;
    const Vec2d CENTER_SELECTION_SIZE = CENTER_SIZE * 1.1;

    const double DISTANCE = SELECTION_SIZE.x + 10;

    sf::RectangleShape selections[SELECTIONS_COUNT];
    for(int i = 0; i < SELECTIONS_COUNT; i++) {
      selections[i] = sf::RectangleShape();
      auto& rect = selections[i];
      rect.setOrigin(SELECTION_SIZE / 2);
      rect.setSize(SELECTION_SIZE);
      Vec2d pos = {500.0 + (i - CENTER) * DISTANCE, 500};
      if(i < CENTER) {
        pos.x -= (CENTER_SELECTION_SIZE.x - SELECTION_SIZE.x) / 2;
      } else {
        pos.x += (CENTER_SELECTION_SIZE.x - SELECTION_SIZE.x) / 2;
      }
      if(i == CENTER) pos = {500.0, 500.0};
      rect.setPosition(pos);
    }
    selections[CENTER].setOrigin(CENTER_SELECTION_SIZE / 2);
    selections[CENTER].setSize(CENTER_SELECTION_SIZE);

    while(window.isOpen() && ship == nullptr) {
      while(const std::optional event = window.pollEvent()) {
        // Keys A-D are used to move the selection left or right
        // And Space/Enter is used to select the ship currently in the middle 
        if(event->is<sf::Event::Closed>()) {
          assets::TextureManager::reset();
          window.close();
          break;
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
      //FIXME: this is very ugly but we can't let the last loop execution
      // come to the next part if the window gets closed
      if(!window.isOpen()) {
        continue;
      }
      window.clear();
      for(int i = 0; i < SELECTIONS_COUNT; i++) {
        window.draw(selections[i]);
        auto& ship =
          *ships[(i - selection_index + ships.size() - CENTER) % ships.size()];
        Vec2d pos = {500.0 + (i - CENTER) * DISTANCE, 500};
        if(i < CENTER) {
          pos.x -= (CENTER_SELECTION_SIZE.x - SELECTION_SIZE.x) / 2;
        } else {
          pos.x += (CENTER_SELECTION_SIZE.x - SELECTION_SIZE.x) / 2;
        }
        if(i == CENTER) pos = {500.0, 500.0};

        if(i == CENTER) {
          Vec2d text_pos = pos + Vec2d(0, CENTER_SELECTION_SIZE.y / 2);
          sf::Text name(*font);
          name.setString(ship.getName());
          name.setPosition(text_pos);
          name.setCharacterSize(50);
          name.setOrigin({name.getLocalBounds().size.x / 2, 0});
          window.draw(name);
        }

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
