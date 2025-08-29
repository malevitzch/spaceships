#include "parts/modules/configs/simple_weapon_config.hpp"

namespace parts {
  SimpleWeaponConfig SimpleWeaponConfig::fromJson(nlohmann::json& data) {
    SimpleWeaponConfig config;
    if(data.contains("anchor")) {
      config.anchor = Anchor::fromJson(data["anchor"]);
    }
    // FIXME: maybe this should consider a vector of projectile configs
    // rather than the information about a single projectile to allow
    // for slightly more complex weapons
    return config;
  }
}
