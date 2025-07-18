#include "core/game.hpp"
#include "assets/texture_manager.hpp"
#include "assets/paths.hpp"
#include "controls/controllers/player_controller.hpp"
#include <chrono>
#include <thread>

namespace core {

  Battle::Battle(sf::RenderWindow& window) : window(window) {}
  void Battle::start() {

    //FIXME: font loader
    sf::Font debug_font;
    if(!debug_font.openFromFile(assets::paths::getAssetsPath()
                                + "/fonts/orbitron/orbitron.ttf")) {
      //TODO: error handling of sorts
    }

    // TODO: the background should maybe be parametrized
    // and the texture accessed through bg_loader or something like that 
    auto bg_texture = assets::TextureManager::getTexture("SpaceBackground");
    sf::Sprite bg_sprite(*bg_texture);

    sf::Clock clock;

    bool over = false;

    sf::Text framerate_text(debug_font);
    framerate_text.setPosition({0, 0});

    double total_time = 0;
    long long total_frames = 0;
    double framerate = 60;

    while(window.isOpen() && !over) {
      total_frames++;
      std::queue<std::optional<sf::Event>> playerEvents;
      while(const std::optional event = window.pollEvent()) {

        if(event->is<sf::Event::Closed>()) {
          window.close();
        } else if(
          const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
          if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
            over = true;
          } else {
            playerEvents.push(event);
          }
        } else {
          // Any event that is not directly consumed by the window itself 
          // is treated as a "PlayerEvent" and sent ahead to the 
          // playerEvents queue
          // FIXME: the contents of the queue should automatically be sent 
          // to every PlayerController
          playerEvents.push(event);
        }
      }

      for(ShipActor& ship : ships) {
        ship.makeDecisions();
      }

      // dt is in seconds
      double dt = clock.getElapsedTime().asSeconds();
      total_time += dt;
      clock.restart();

      for(ShipActor& ship : ships) {
        ship.physicsTick(dt);
      }


      window.clear();

      window.draw(bg_sprite);
      for(ShipActor& ship : ships) {
        window.draw(ship, sf::RenderStates());
      }

      if(total_frames % 10 == 0) framerate = total_frames / total_time;
      framerate_text.setString(std::to_string((int) framerate) + " fps");
      window.draw(framerate_text);

      window.display();
      if(dt < frame_length) {
        // This is in milliseconds because sleep works with integers
        int wait_time = (frame_length - dt) * 1000;

        // Warning: the +10 here fixes a certain problem for 60fps but might
        // be a limiter for when someone wants to run the game in 144fps
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time + 10));
      }
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
