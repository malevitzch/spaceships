#include "assets/sprite_manager.hpp"
#include <stdexcept>

namespace assets {
  std::map<std::string,
           SpriteManager::ShipSpriteInfo> SpriteManager::sprites = {
    {"Bird",    {"BasicShip", {50, 50}, {15, 25}, 1}},
    {"BorgMk1", {"OmniShip", {50, 50}, {25, 25}, 1}},
    {"BorgMk2", {"OmniShipMk2", {50, 50}, {25, 25}, 1}},
    {"Round",   {"Round", {50, 50}, {25, 25}, 1}},
    {"Cobra",   {"Cobra", {256, 256}, {128, 128}, 50.0 / 256.0}},
    {"Bug",     {"Bug", {256, 256}, {100, 128}, 50.0 / 256.0}},
  };
  std::shared_ptr<core::ShipSprite> SpriteManager::ShipSpriteInfo::get() {
    if(sprite == nullptr) {
      sprite = std::make_shared<core::ShipSprite>(texture_name,
                                                  center_of_mass,
                                                  sprite_size,
                                                  scale);
    }
    return sprite;
  }


  std::shared_ptr<core::ShipSprite> SpriteManager::getShipSprite(std::string name) {
    if(!sprites.contains(name)) {
      throw std::runtime_error("Unknown sprite name: \"" + name + "\"");
    }
    return sprites[name].get();
  }
}
