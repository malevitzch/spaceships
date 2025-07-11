#include "core/game.hpp"
#include "assets/texture_manager.hpp"
#include "controls/controllers/player_controller.hpp"

namespace core {

  ShipActor::ShipActor(
    std::shared_ptr<parts::SpaceshipCore> core,
    std::shared_ptr<controls::Controller> controller)
      : core(core), controller(controller) {}

  Battle::Battle(sf::RenderWindow& window) : window(window) {}
  void Battle::start() {
    // FIXME: make an asset load system
    // TODO: the background should maybe be parametrized
    // and the texture accessed through bg_loader or something like that 
    auto bg_texture = assets::TextureManager::getTexture("SpaceBackground");
    sf::Sprite bg_sprite(*bg_texture);

    sf::Clock clock;

    bool over = false;
    while(window.isOpen() && !over) {
      std::queue<std::optional<sf::Event>> playerEvents;
      while(const std::optional event = window.pollEvent()) {

        if(event->is<sf::Event::Closed>()) {
          window.close();
        } else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
          if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
            over = true;
          } else {
            playerEvents.push(event);
          }
        } else {
          // Any event that is not directly consumed by the window itself is treated 
          // as a "PlayerEvent" and sent ahead to the playerEvents queue which is then
          // passed as an argument to the function that strips player input from events
          playerEvents.push(event);
        }
      }

      // dt is in seconds
      double dt = clock.getElapsedTime().asSeconds();
      clock.restart();

      for(ShipActor& ship : ships) {
        auto& core = *ship.core;

        // This contains all player input (or the input of a machine-controlled ship)
        controls::ShipOrders orders = ship.controller->getOrders();

        // SpaceshipCore processes input and acts depending on them
        // This is really convenient as different types of esoteric ships might
        // not necessarily operate under the same rules 
        core.handleInstructions(orders);

        core.physicsTick(dt);
      }


      window.clear();
      window.draw(bg_sprite);
      for(ShipActor& ship : ships)
        window.draw(*ship.core, sf::RenderStates());

      window.display();
    }

  }

  void Battle::addShip(ShipActor ship) {
    ships.push_back(ship);
  }
  void Battle::addPlayerShip(
    ShipActor ship,
    std::shared_ptr<controls::PlayerController> player) {
    addShip(ship);
    players.push_back(player);
  }

}
