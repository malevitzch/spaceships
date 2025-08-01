#include "core/game.hpp"
#include "core/camera.hpp"
#include "assets/font_manager.hpp"
#include "assets/texture_manager.hpp"
#include "controls/controllers/player_controller.hpp"
#include <chrono>
#include <memory>
#include <thread>

namespace core {

  Battle::Battle(sf::RenderWindow& window) : window(window), camera(window) {}
  void Battle::start() {
    camera.setPosition({0, 0});

    std::shared_ptr<sf::Font> debug_font = assets::FontManager::getFont("orbitron");

    constexpr int BUFFER_SIZE = 100;
    float frame_times[BUFFER_SIZE] = {};
    int frame_index = 0;
    bool buffer_filled = false;
    sf::Clock frame_clock;
    sf::Clock fps_clock;

    over = false;

    sf::Text framerate_text(*debug_font);
    framerate_text.setPosition({0, 0});

    while(window.isOpen() && !over) {
      float dt = frame_clock.restart().asSeconds();

      processEvents();

      for(ShipActor& ship : ships) {
        ship.makeDecisions();
      }

      for(ShipActor& ship : ships) {
        ship.physicsTick(dt);
      }

      camera.moveTowards(player_ship->getPosition(), dt);

      frame_times[frame_index] = dt;
      frame_index = (frame_index + 1) % BUFFER_SIZE;
      if (frame_index == 0) buffer_filled = true;

      int count = buffer_filled ? BUFFER_SIZE : frame_index;
      float total_time = 0.f;
      for (int i = 0; i < count; ++i) {
        total_time += frame_times[i];
      }
      float average_dt = total_time / count;

      if (fps_clock.getElapsedTime().asSeconds() >= target_fps_time) {
        fps_clock.restart();
        int fps = static_cast<int>(1.f / average_dt);
        framerate_text.setString(std::to_string(fps) + " fps");
      }

      window.clear();
      camera.drawBackground();
      camera.drawShips(ships);
      window.draw(framerate_text);
      window.display();

      float elapsed = frame_clock.getElapsedTime().asSeconds();
      if (elapsed < target_frame_time) {
        int sleep_ms = static_cast<int>((target_frame_time - elapsed) * 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
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
    player->battle = this;
    players.push_back(player);
  }

  const Camera& Battle::getCamera() const {
    return camera;
  }
  sf::Window& Battle::getWindow() {
    return window;
  }

  void Battle::processEvents() {
    std::queue<std::optional<sf::Event>> player_events;
    while(const std::optional event = window.pollEvent()) {

      if(event->is<sf::Event::Closed>()) {
        window.close();
      }
      // This is a bit ugly but it handles keypresses which we don't want
      // to be related to the player's actions but to the game itself
      // like pressing "Escape" to leave go back to hangar
      else if(const auto* key_pressed =
        event->getIf<sf::Event::KeyPressed>()) {
        switch(key_pressed->scancode) {
          case sf::Keyboard::Scancode::Escape:
            over = true;
            break;
          default:
            player_events.push(event);
            break;
        }
      } else {
        // Any event that is not directly consumed by the window itself
        // is treated as a "PlayerEvent" and sent ahead to the
        // player_events queue
        player_events.push(event);
      }
    }

    // Send out the player_events to their corresponding player
    while(!player_events.empty()) {
      for(auto player : players) {
        player->addEvent(*player_events.front());
      }
      player_events.pop();
    }

  }

}
