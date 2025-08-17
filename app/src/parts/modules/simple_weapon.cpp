#include "parts/modules/simple_weapon.hpp"
#include "core/objects/simple_projectile.hpp"
#include "parts/cores/ship_core.hpp"
#include "core/game.hpp"

namespace parts {

  SimpleWeapon::SimpleWeapon(int signal_code,
                             double cooldown,
                             std::string projectile_sprite_name,
                             util::Vec2d offset,
                             util::Angle rotation,
                             double projectile_velocity,
                             double projectile_duration)
  : SimpleTriggerModule(signal_code, cooldown),
    projectile_sprite_name(projectile_sprite_name),
    offset(offset),
    rotation(rotation),
    projectile_velocity(projectile_velocity),
    projectile_duration(projectile_duration) {}

  void SimpleWeapon::trigger() {
    using util::Vec2d;
    auto& core = getCore();
    Vec2d source = core.getPosition() + offset.rotated(core.getAngle());
    Vec2d velocity = Vec2d(projectile_velocity, core.getAngle() + rotation) + core.getVelocity();

    auto& battle = core.getBattle();
    battle.addObject(
      std::make_unique<core::SimpleProjectile>(
        projectile_sprite_name,
        source,
        velocity,
        Vec2d(0, 0),
        core.getAngle(),
        projectile_duration
    ));
  }
}
