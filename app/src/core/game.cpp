#include "core/game.hpp"
#include "core/camera.hpp"
#include "assets/font_manager.hpp"
#include "assets/texture_manager.hpp"
#include "controls/controllers/player_controller.hpp"
#include "core/objects/simple_projectile.hpp"
#include <chrono>
#include <memory>
#include <thread>

namespace core {

  using util::Vec2d;

  Battle::Battle(sf::RenderWindow& window) : window(window), camera(window) {}
  void Battle::start() {
    camera.setPosition({0, 0});

    std::shared_ptr<sf::Font> debug_font =
      assets::FontManager::getFont("orbitron");

    constexpr int BUFFER_SIZE = 500;
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
      // If the processing of events causes the window to close,
      // we need to immediately exit the loop because SFML textures
      // require a valid OpenGL context which (on some systems) 
      // is destroyed when the window is closed
      if(!window.isOpen()) break;

      // Cleanup old objects such as expired projectiles
      for(int i = 0; i < objects.size(); i++) {
        while(i < objects.size() && objects[i]->isDestroyed()) {
          std::swap(objects[i], objects.back());
          objects.pop_back();
        }
      }

      for(ShipActor& ship : ships) {
        ship.makeDecisions();
      }

      for(ShipActor& ship : ships) {
        ship.physicsTick(dt);
      }

      for(std::shared_ptr<SpaceObject> object : objects) {
        object->physicsTick(dt);
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
      camera.drawObjects(objects);
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

  void Battle::addShip(ShipActor ship, int team) {
    ship.setTeam(team);
    // The point of this line is to give the ship access to the battle
    // context, which is mostly used by modules that want to for example
    // spawn projectiles
    ship.getShip().getCore().setBattle(this);
    ships.push_back(ship);
  }
  void Battle::addPlayerShip(
      ShipActor ship,
      std::shared_ptr<controls::PlayerController> player) {

    addShip(ship, 0);

    player_ship = ship.getShipPointer();
    player->setBattle(this);
    players.push_back(player);
  }

  void Battle::addObject(std::shared_ptr<SpaceObject> object) {
    objects.push_back(object);
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
        assets::TextureManager::reset();
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
      } else if(const auto* mouse_pressed =
        event->getIf<sf::Event::MouseButtonPressed>()) {
        switch(mouse_pressed->button) {
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
  std::shared_ptr<Ship> Battle::getPlayerShip() const {
    return player_ship;
  }

}
