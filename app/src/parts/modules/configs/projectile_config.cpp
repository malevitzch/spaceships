#include "parts/modules/configs/projectile_config.hpp"
#include <random>
#include <algorithm>

namespace parts {
  std::vector<std::shared_ptr<core::SpaceObject>>
    ProjectileConfig::spawn(util::Vec2d source, util::Angle direction) const {
    //TODO: decide something about the number generator, for now this is enough
    static std::mt19937 rng(std::random_device{}());
    static std::normal_distribution<double> dist(0.0, 0.3);


    std::vector<std::shared_ptr<core::SpaceObject>> res;
    for(int i = 0; i < count; i++) {
      double deviation = spread * std::clamp(dist(rng), -1.0, 1.0);
      util::Angle target_angle = direction + deviation;
      res.push_back(
        std::make_shared<core::SimpleProjectile>(
          sprite_name,
          source,
          util::Vec2d(velocity, target_angle),
          util::Vec2d(0, 0), //TODO: investigate what this is (probably acceleration)
          target_angle,
          duration));
    }

    return res;
  }
  ProjectileConfig ProjectileConfig::fromJson(nlohmann::json& data) {
    ProjectileConfig config;
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
    return config;
  }
}
