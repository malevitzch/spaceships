#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Clock.hpp>
#include "controls/controllers/player_controller.hpp"
#include "core/game.hpp"
#include "core/menu.hpp"
#include "core/ship_actor.hpp"
#include "parts.hpp"


int main() {
  auto window = sf::RenderWindow(sf::VideoMode({1000, 1000}), "Main Window");
  window.setPosition({0, 0});
  //TODO: don't hard limit to 144
  window.setFramerateLimit(144);

  core::Menu menu(window);

  while(window.isOpen()) {

    auto ship = menu.pickShip();

    // If ship selection fails it's usually becuase user closed the window
    // in which case we want to avoid things like nullptr dereferences
    // and we just exit the program with code 0
    if(ship == nullptr) return 0;

    core::Battle battle(window);
    std::shared_ptr<controls::PlayerController> player_controller
      = std::make_shared<controls::PlayerController>();
    core::ShipActor player(
      ship,
      player_controller,
      "OmniShip"
    );

    player.ship->getCore().setPosition({0, 0});

    battle.addPlayerShip(player, player_controller);
    battle.start();
  }
  return 0;
}
