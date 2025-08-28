#include "utility/vec2d.hpp"

namespace parts {

  struct SimpleWeaponConfig {
    util::Vec2d offset = {0, 0};
    util::Angle rotation = 0.0;
    std::string projectile_sprite_name;
    double projectile_velocity;
    double projectile_duration;
    double spread = 0.0;
  };

}
