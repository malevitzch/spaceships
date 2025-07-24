#include "core/game.hpp"
#include "core/camera.hpp"
#include "assets/font_manager.hpp"
#include "assets/texture_manager.hpp"
#include "controls/controllers/player_controller.hpp"
#include <chrono>
#include <memory>
#include <thread>

namespace core {

  Battle::Battle(sf::RenderWindow& window) : window(window) {}
  void Battle::start() {

    std::shared_ptr<sf::Font> debug_font = assets::FontManager::getFont("orbitron");

    sf::Clock clock;

    bool over = false;

    sf::Text framerate_text(*debug_font);
    framerate_text.setPosition({0, 0});

    double total_time = 0;
    long long total_frames = 0;
    double framerate = 60;

    Camera camera(window);

    while(window.isOpen() && !over) {
      total_frames++;
      std::queue<std::optional<sf::Event>> playerEvents;
      while(const std::optional event = window.pollEvent()) {

        if(event->is<sf::Event::Closed>()) {
          window.close();
        }
        // This is a bit ugly but it handles keypresses which we don't want
        // to be related to the player's actions but to the game itself
        // like pressing "Escape" to leave go back to hangar
        // TODO: consider switch statement
        else if(const auto* keyPressed =
          event->getIf<sf::Event::KeyPressed>()) {

          if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
            over = true;
          } else {
            playerEvents.push(event);
          }
        } else {
          // Any event that is not directly consumed by the window itself 
          // is treated as a "PlayerEvent" and sent ahead to the 
          // playerEvents queue
          playerEvents.push(event);
        }
      }

      // Send out the playerEvents to their corresponding pr
      while(!playerEvents.empty()) {
        for(auto player : players) {
          player->addEvent(*playerEvents.front());
        }
        playerEvents.pop();
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

      //window.draw(bg_sprite);
      camera.moveTowards(player_ship->getPosition(), dt);
      camera.drawBackground();
      camera.drawShips(ships);
      /*for(ShipActor& ship : ships) {
        window.draw(ship, sf::RenderStates());
      }*/

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
    player_ship = ship.ship;
    players.push_back(player);
  }

}
