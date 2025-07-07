#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Clock.hpp>
#include <stdexcept>
#include "parts.hpp"


// TODO: this should not be a part of the main function but rather a part of 
// a battle so that menu is separate from the game logic once a menu is created
int main() {
  auto window = sf::RenderWindow(sf::VideoMode({1000, 1000}), "Main Window");
  window.setPosition({0, 0});
  window.setFramerateLimit(144);

  parts::SimpleCore core;
  core.setPosition({500, 500});
  sf::Clock clock;

  // FIXME: make an asset load system
  sf::Texture bg_texture; 
  if(!bg_texture.loadFromFile("assets/graphics/SpaceBackground.png")) {
    throw new std::runtime_error("Failed to load texture for background");
  }

  sf::Sprite bg_sprite(bg_texture);

  while (window.isOpen()) {
    std::queue<std::optional<sf::Event>> playerEvents;
    while (const std::optional event = window.pollEvent()) {

      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      // TODO: this block of code is temporary and only exists for debug purposes
      // It's not a part of the ship control system
      else if (event->is<sf::Event::MouseButtonPressed>()) {
        const auto& mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
        if(mouseEvent->button == sf::Mouse::Button::Left) {
          core.setPosition({(double)mouseEvent->position.x, (double)mouseEvent->position.y});
        }
      } else {
        // Any event that is not directly consumed by the window itself is treated 
        // as a "PlayerEvent" and sent ahead to the playerEvents queue which is then
        // passed as an argument to the function that strips player input from events
        playerEvents.push(event);
      }
    }

    // This contains all player input (which will ultimately contain things like mouse clicks)
    // And it should
    controls::ShipOrders player_input = controls::getPlayerOrders(playerEvents);

    // SpaceshipCore processes input and acts depending on them
    // This is really convenient as different types of esoteric ships might
    // not necessarily operate under the same rules as SimpleCore
    core.handleInstructions(player_input);

    // dt is in seconds
    double dt = clock.getElapsedTime().asSeconds();
    clock.restart();
    core.physicsTick(dt);

    window.clear();
    window.draw(bg_sprite);

    core.draw(window, sf::RenderStates());

    window.display();
  }
}
