#include "parts/modules/simple_weapon.hpp"
#include "core/objects/simple_projectile.hpp"
#include "parts/cores/ship_core.hpp"
#include "core/game.hpp"

#include <random>
#include <algorithm>
#include <vector>

namespace parts {

  SimpleWeapon::SimpleWeapon(int signal_code, SimpleWeaponConfig config)
  : SimpleTriggerModule(signal_code, config.cooldown) {
    anchor = config.anchor;
    name = config.name;
    projectiles = config.projectiles;
  }

  void SimpleWeapon::trigger() {
    auto& core = getCore();

    std::vector<std::shared_ptr<core::SpaceObject>> projectiles;

    util::Vec2d source = core.getPosition();
    util::Angle angle = core.getAngle();
    util::Vec2d velocity = core.getVelocity();

    for(auto& projectile_config : this->projectiles) {
      for(auto projectile : projectile_config.spawn(source, angle, velocity)) {
        projectiles.push_back(projectile);
      }
    }

    auto& battle = core.getBattle();
    battle.addObjects(projectiles);
  }
}
