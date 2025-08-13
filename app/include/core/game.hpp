#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "controls/controllers/player_controller.hpp"
#include "core/objects/space_object.hpp"
#include "core/ship_actor.hpp"
#include "core/camera.hpp"

namespace core {

  class Battle {
  private:
    bool over = false;

    // TODO: this can be set to something reasonable
    // like 60 or 144 but for now is pretty much uncapped
    // so that the performance effects of various
    // design decisions can be seen
    const double target_frame_time = 0.0000001; // e.g = 1.0f / 144.0f for 144 fps
    const double target_fps_time = 0.2f;        // frequency of updating fps

    sf::RenderWindow& window;
    Camera camera;

    // The removal of destroyed ships is done simply by
    // swapping with the last one and doing pop_back
    // This is "inefficient" but is generally done rarely
    // compared to usual iteration
    std::vector<ShipActor> ships;
    std::vector<std::shared_ptr<SpaceObject>> objects;
    std::shared_ptr<Ship> player_ship;
    std::vector<std::shared_ptr<controls::PlayerController>> players;
  public:
    Battle(sf::RenderWindow& window);

    virtual void start();

    void addShip(ShipActor ship, int team);
    void addPlayerShip(
      ShipActor ship,
      std::shared_ptr<controls::PlayerController> player);

    void addObject(std::shared_ptr<SpaceObject> object);

    virtual void processEvents();

    const Camera& getCamera() const;
    sf::Window& getWindow();
  };

}

#endif
