#include "utility/vec2d.hpp"
#include "nlohmann/json.hpp"

#include "anchor.hpp"
#include "projectile_config.hpp"

namespace parts {

  struct SimpleWeaponConfig {
    std::string name;
    Anchor anchor;
    std::vector<ProjectileConfig> projectiles = {};
    double cooldown = 1.0;

    static SimpleWeaponConfig fromJson(nlohmann::json& data);
  };

}
