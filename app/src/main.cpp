#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Clock.hpp>
#include "assets/sprite_manager.hpp"
#include "controls/controllers/enemy_controller.hpp"
#include "controls/controllers/player_controller.hpp"
#include "core/game.hpp"
#include "core/menu.hpp"
#include "core/ship_actor.hpp"


#include "parts/cores.hpp"
#include "core/ship.hpp"

int main() {
  assets::SpriteManager::init();

  auto window = sf::RenderWindow(sf::VideoMode({1000, 1000}), "Main Window");
  window.setPosition({0, 0});

  // Avoids firing the last keypress multiple times which caused inconsistent
  // and unintuitive behavior
  window.setKeyRepeatEnabled(false);

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
    core::ShipActor player(ship, player_controller);
    player.getShip().getCore().setPosition({0, 0});

    battle.addPlayerShip(player, player_controller);

    // FIXME: remove or something
    /*
    std::shared_ptr<controls::EnemyController> enemy_controller
      = std::make_shared<controls::EnemyController>();
    std::shared_ptr<core::Ship> enemy_ship 
      = std::make_shared<core::Ship>("Phage Mk. 1",
                                     std::make_shared<parts::SimpleCore>(50, 4),
                                     "Phage");
    core::ShipActor enemy(enemy_ship, enemy_controller);
    battle.addShip(enemy, 1);
    */

    battle.start();
  }
  return 0;
}
