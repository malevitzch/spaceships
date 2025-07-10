#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Clock.hpp>
#include "controls/controllers/player_controller.hpp"
#include "core/game.hpp"
#include "core/menu.hpp"
#include "parts.hpp"


int main() {
  auto window = sf::RenderWindow(sf::VideoMode({1000, 1000}), "Main Window");
  window.setPosition({0, 0});
  window.setFramerateLimit(144);

  core::Menu menu(window);

  while(window.isOpen()) {
    auto ship = menu.pickShip();

    // If ship selection fails it's usually becuase user closed the window
    if(ship == nullptr) return 0;

    core::Battle battle(window);
    std::shared_ptr<controls::PlayerController> player_controller
      = std::make_shared<controls::PlayerController>();
    core::ShipActor player(
      ship,
      player_controller
    );

    player.core->setPosition({500, 500});

    battle.addPlayerShip(player, player_controller);
    battle.start();
  }
}
