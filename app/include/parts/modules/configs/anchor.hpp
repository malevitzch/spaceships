#ifndef PARTS_MODULES_CONFIGS_ANCHOR_HPP
#define PARTS_MODULES_CONFIGS_ANCHOR_HPP

#include "utility/vec2d.hpp"
#include "nlohmann/json.hpp"

namespace parts {
  struct Anchor {
    util::Vec2d offset = {0, 0};
    util::Angle angle = 0.0;

    static Anchor fromJson(nlohmann::json& json);
  };
}

#endif
