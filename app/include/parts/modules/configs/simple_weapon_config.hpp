#include "utility/vec2d.hpp"
#include "nlohmann/json.hpp"

#include "anchor.hpp"

namespace parts {

  struct SimpleWeaponConfig {
    Anchor anchor;
    std::string projectile_sprite_name;
    double projectile_velocity;
    double projectile_duration;
    double spread = 0.0;

    static SimpleWeaponConfig fromJson(nlohmann::json& data);
  };

}
