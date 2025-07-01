#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Clock.hpp>
#include "parts/cores/simple_core.hpp"

int main() {
  auto window = sf::RenderWindow(sf::VideoMode({1000, 1000}), "Main Window");
  window.setPosition({0, 0});
  window.setFramerateLimit(144);

  parts::SimpleCore core;
  sf::Clock clock;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (event->is<sf::Event::MouseButtonPressed>()) {
        const auto& mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
        if(mouseEvent->button == sf::Mouse::Button::Left) {
          core.setPosition({(double)mouseEvent->position.x, (double)mouseEvent->position.y});
        }
      }
    }
    controls::PlayerInput player_input;
    player_input.ahead = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    player_input.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    player_input.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    core.handleInstructions(player_input);
    // dt is in seconds
    double dt = clock.getElapsedTime().asSeconds();
    clock.restart();
    core.physicsTick(dt);

    window.clear();
    core.draw(window, sf::RenderStates());

    window.display();
  }
}
