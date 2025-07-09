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

  // TODO: the following part is still not the initial setup
  // instead, we should have a menu that starts a new battle
  parts::OmniCore core;

  core::Menu menu(window);

  auto ship = menu.pickShip();
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
