#ifndef PARTS_MODULES_CONFIGS_SIMPLE_PROJECTILE_CONFIG_HPP
#define PARTS_MODULES_CONFIGS_SIMPLE_PROJECTILE_CONFIG_HPP

#include "utility/vec2d.hpp"
#include "nlohmann/json.hpp"

#include "core/objects/simple_projectile.hpp"

namespace parts {
  struct ProjectileConfig {
    // TODO: default sprite, maybe something silly, so that
    // so that the game doesn't crash
    std::string sprite_name;
    int count = 1;
    double velocity = 1000;
    double duration = 2; // Duration in seconds
    double spread = 0.0; // Spread is in RADIANS
    double rotation = 0.0; // In radians too
    util::Vec2d offset = {0.0, 0.0};

    std::vector<std::shared_ptr<core::SpaceObject>> spawn(
      util::Vec2d source,
      util::Angle direction,
      util::Vec2d initial_velocity) const;
    static ProjectileConfig fromJson(nlohmann::json& data);
  };
}

#endif
