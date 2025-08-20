#include "controls/controllers/enemy_controller.hpp"
#include "core/game.hpp"
#include "utility/vec2d.hpp"
#include <cmath>

namespace controls {
  ShipOrders EnemyController::getOrders(core::Ship& ship) {
    using util::Vec2d;
    ShipOrders orders;

    auto& my_core = ship.getCore();
    Vec2d my_pos = my_core.getPosition();

    auto& player_core = battle->getPlayerShip()->getCore();
    Vec2d player_pos = player_core.getPosition();

    Vec2d target_vector = util::vecBetween(my_pos, player_pos);
    Vec2d direction_vector = util::Vec2d::unit(my_core.getAngle());
    if(std::fabs(my_core.getAngularVelocity()) > 1) {
      if(my_core.getAngularVelocity() > 0) {
        orders.left = true;
      } else {
        orders.right = true;
      }
    }
    else if(util::vectorProduct(direction_vector, target_vector) > 0) {
      orders.right = true;
    } else {
      orders.left = true;
    }

    return orders;
  }
}
