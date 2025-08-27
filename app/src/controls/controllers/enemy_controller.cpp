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
    double angular_velocity = core.getAngularVelocity();

    double rdist = util::mathfmod(target_angle - my_angle, std::numbers::pi * 2);
    double ldist = std::numbers::pi * 2 - rdist;

    return orders;
  }
}
