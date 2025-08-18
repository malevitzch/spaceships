#include "controls/controllers/enemy_controller.hpp"
#include "core/game.hpp"
#include "utility/vec2d.hpp"


namespace controls {
  ShipOrders EnemyController::getOrders() {
    ShipOrders orders;

    auto& player_core = battle->getPlayerShip()->getCore();
    util::Vec2d player_pos = player_core.getPosition();


    return orders;
  }
}
