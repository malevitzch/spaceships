#include "parts/modules/configs/simple_weapon_config.hpp"
#include <iostream>

#include "logs/logger.hpp"

namespace parts {
  SimpleWeaponConfig SimpleWeaponConfig::fromJson(nlohmann::json& data) {
    SimpleWeaponConfig config;
    if(data.contains("name")) {
      config.name = data["name"];
    } else {
      config.name = "___Anonymous___";
    }
    if(data.contains("anchor")) {
      config.anchor = Anchor::fromJson(data["anchor"]);
    }
    if(data.contains("projectiles")) {
      for(auto& pdata : data["projectiles"]) {
        config.projectiles.push_back(ProjectileConfig::fromJson(pdata));
      }
    }
    if(data.contains("cooldown")) {
      config.cooldown = data["cooldown"];
    }
    return config;
  }
}
