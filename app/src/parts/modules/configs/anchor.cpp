#include "parts/modules/configs/anchor.hpp"

namespace parts {
  Anchor Anchor::fromJson(nlohmann::json& data) {
    Anchor anchor;
    if(data.contains("offset")) {
      //TODO: allow for writing offset with only one value
      // for example "offset" : {"y" : 30} being valid and giving 
      // an anchor without x offset and only y one
      anchor.offset = {data["offset"]["x"], data["offset"]["y"]};
    }

    if(data.contains("angle")) {
      anchor.angle = double(data["angle"]);
    }

    return anchor;
  }
}
