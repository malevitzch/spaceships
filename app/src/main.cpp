#include <SFML/Graphics.hpp>

int main() {
  auto window = sf::RenderWindow(sf::VideoMode({1000, 1000}), "Main Window");
  window.setPosition({0, 0});
  window.setFramerateLimit(144);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear();
    window.display();
  }
}
