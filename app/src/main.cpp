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
    }
    double dt = clock.getElapsedTime().asMilliseconds();
    clock.restart();
    core.physicsTick(dt);

    window.clear();
    core.draw(window, sf::RenderStates());

    window.display();
  }
}
