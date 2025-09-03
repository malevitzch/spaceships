#include "parts/modules/configs/anchor.hpp"

namespace parts {
  Anchor Anchor::fromJson(nlohmann::json& data) {
    Anchor anchor;
    if(data.contains("offset")) {
      if(data["offset"].contains("x")) {
        anchor.offset.x = data["offset"]["x"];
      }
      if(data["offset"].contains("y")) {
        anchor.offset.y = data["offset"]["y"];
      }
    }

    if(data.contains("angle")) {
      anchor.angle = double(data["angle"]);
    }

    return anchor;
  }
}
