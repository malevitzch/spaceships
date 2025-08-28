#include "parts/modules/simple_weapon.hpp"
#include "core/objects/simple_projectile.hpp"
#include "parts/cores/ship_core.hpp"
#include "core/game.hpp"

#include <random>
#include <algorithm>

namespace parts {

  SimpleWeapon::SimpleWeapon(int signal_code,
                             double cooldown,
                             std::string projectile_sprite_name,
                             util::Vec2d offset,
                             util::Angle rotation,
                             double projectile_velocity,
                             double projectile_duration,
                             double spread)
  : SimpleTriggerModule(signal_code, cooldown),
    projectile_sprite_name(projectile_sprite_name),
    offset(offset),
    rotation(rotation),
    projectile_velocity(projectile_velocity),
    projectile_duration(projectile_duration),
    spread(spread) {}

  void SimpleWeapon::trigger() {
    using util::Vec2d;

    static std::mt19937 rng(std::random_device{}());
    static std::normal_distribution<double> dist(0.0, 0.3);

    auto& core = getCore();

    Vec2d source = core.getPosition() + offset.rotated(core.getAngle());

    double deviation = spread * std::clamp(dist(rng), -1.0, 1.0);
    util::Angle target_angle = core.getAngle() + deviation + rotation;

    Vec2d velocity = Vec2d(projectile_velocity, target_angle) + core.getVelocity();


    auto& battle = core.getBattle();
    battle.addObject(
      std::make_unique<core::SimpleProjectile>(
        projectile_sprite_name,
        source,
        velocity,
        Vec2d(0, 0),
        target_angle,
        projectile_duration
    ));
  }
}
