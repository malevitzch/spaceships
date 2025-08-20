#include "controls/controllers/enemy_controller.hpp"
#include "core/game.hpp"
#include "utility/angle.hpp"
#include "utility/vec2d.hpp"

#include "parts/cores/simple_core.hpp"

#include <cmath>

namespace controls {
  ShipOrders EnemyController::getOrders(core::Ship& ship) {
    using util::Vec2d;
    using util::Angle;
    ShipOrders orders;

    auto& my_core = ship.getCore();
    Vec2d my_pos = my_core.getPosition();

    auto& player_core = battle->getPlayerShip()->getCore();
    Vec2d player_pos = player_core.getPosition();

    Vec2d target_vector = util::vecBetween(my_pos, player_pos);
    Vec2d direction_vector = util::Vec2d::unit(my_core.getAngle());

    Angle my_angle = my_core.getAngle();
    Angle target_angle = target_vector.angle();

    parts::SimpleCore& core = dynamic_cast<parts::SimpleCore&>(my_core);
    double angular_thrust = core.getAngularThrust();

    bool side = false;

    double stopping_angle = std::pow(core.getAngularVelocity(), 2) / angular_thrust;

    if(my_core.getAngularVelocity() > 0) {
      double distance = util::mathfmod(target_angle - my_angle, 2*std::numbers::pi);
      side = (distance < stopping_angle);
    } else {
      double distance = util::mathfmod(my_angle - target_angle, 2*std::numbers::pi);
      side = (distance > stopping_angle);
    }

    if(side) orders.left = true; else orders.right = true;

    return orders;
  }
}
