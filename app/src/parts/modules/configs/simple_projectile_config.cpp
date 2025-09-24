#include "parts/modules/configs/simple_projectile_config.hpp"
#include "logs/logger.hpp"
#include <random>
#include <algorithm>

namespace parts {
  std::vector<std::shared_ptr<core::SpaceObject>>
    ProjectileConfig::spawn(util::Vec2d source,
                            util::Angle direction,
                            util::Vec2d initial_velocity) const {
    // TODO: decide something about the random number generator,
    // but for now this is enough
    static std::mt19937 rng(std::random_device{}());
    static std::normal_distribution<double> dist(0.0, 0.3);

    source += offset.rotated(direction);

    std::vector<std::shared_ptr<core::SpaceObject>> res;
    for(int i = 0; i < count; i++) {
      double deviation = spread * std::clamp(dist(rng), -1.0, 1.0);
      util::Angle target_angle = direction + rotation + deviation;
      res.push_back(
        std::make_shared<core::SimpleProjectile>(
          sprite_name,
          source,
          util::Vec2d(velocity, target_angle) + initial_velocity,
          util::Vec2d(0, 0),
          target_angle,
          duration));
    }

    return res;
  }
  ProjectileConfig ProjectileConfig::fromJson(nlohmann::json& data) {
    ProjectileConfig config;
    if(data.contains("sprite_name")) {
      config.sprite_name = data["sprite_name"];
    } else {
      logs::Logger::logError("Projectile without sprite name");
      // FIXME: sprite name is mandatory (or at least there should be a default
      // stock sprite that is used rather than an empty string)
    }
    if(data.contains("count")) {
      config.count = data["count"];
    }
    if(data.contains("velocity")) {
      config.velocity = data["velocity"]; 
    }
    if(data.contains("duration")) {
      config.duration = data["duration"];
    }
    if(data.contains("spread")) {
      config.spread = data["spread"];
    }
    if(data.contains("rotation")) {
      config.rotation = data["rotation"];
    }
    if(data.contains("offset")) {
      // TODO:validate if offset is a composite type
      if(data["offset"].contains("x")) config.offset.x = data["offset"]["x"];
      if(data["offset"].contains("y")) config.offset.y = data["offset"]["y"];
    }

    return config;
  }
}
