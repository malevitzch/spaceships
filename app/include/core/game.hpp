#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "controls/controllers/player_controller.hpp"
#include "parts/cores/spaceship_core.hpp"
#include "controls/controllers/controller.hpp"
#include "core/ship_actor.hpp"

namespace core {

  class Battle {
  private:
    // TODO: this can be set to something reasonable
    // like 60 or 144 but for now is pretty much uncapped
    // so that the performance effects of various
    // design decisions can be seen
    const double frame_length = 0.0000001;
    sf::RenderWindow& window;

    // The removal of destroyed ships is done simply by
    // swapping with the last one and doing pop_back
    // This is "inefficient" but is generally done rarely
    // compared to usual iteration
    std::vector<ShipActor> ships;
    std::vector<std::shared_ptr<controls::PlayerController>> players;
  public:
    Battle(sf::RenderWindow& window);

    virtual void start();

    void addShip(ShipActor ship);
    void addPlayerShip(
      ShipActor ship,
      std::shared_ptr<controls::PlayerController> player);
  };

}

#endif
