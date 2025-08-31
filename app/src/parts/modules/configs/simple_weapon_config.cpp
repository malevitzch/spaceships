#include "parts/modules/configs/simple_weapon_config.hpp"
#include <iostream>

namespace parts {
  SimpleWeaponConfig SimpleWeaponConfig::fromJson(nlohmann::json& data) {
    SimpleWeaponConfig config;
    if(data.contains("name")) {
      config.name = data["name"];
    } else {
      // FIXME: this field is mandatory, weapons need a name
      // and we can't give a default one since it would mess
      // with any maps of weapon information since the name is
      // the natural public key for them
      // (add some exception or something here)
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
    std::cout << config.projectiles.size();
    return config;
  }
}
