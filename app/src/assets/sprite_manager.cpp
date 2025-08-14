#include "assets/sprite_manager.hpp"
#include "assets/paths.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <stdexcept>

namespace assets {
  std::map<std::string,
           SpriteManager::ShipSpriteInfo> SpriteManager::sprites;
  std::shared_ptr<core::ShipSprite> SpriteManager::ShipSpriteInfo::get() {
    if(sprite == nullptr) {
      sprite = std::make_shared<core::ShipSprite>(texture_name,
                                                  center_of_mass,
                                                  sprite_size,
                                                  scale);
    }
    return sprite;
  }

  void SpriteManager::init() {
    loadShipSprites();
  }

  void SpriteManager::loadShipSprites() {
    using nlohmann::json;
    std::ifstream spritestream(
      assets::paths::getAssetsPath() + "/json/ship_sprites.json");
    json data = json::parse(spritestream);
    for(auto& sprite_data : data["sprites"]) {
      sprites[sprite_data["name"]] = {
        sprite_data["filename"],
        {sprite_data["size"]["x"], sprite_data["size"]["y"]},
        {sprite_data["origin"]["x"], sprite_data["origin"]["y"]},
        sprite_data["scale"]
      };
    }
  }

  std::shared_ptr<core::ShipSprite> SpriteManager::getShipSprite(std::string name) {
    if(!sprites.contains(name)) {
      throw std::runtime_error("Unknown sprite name: \"" + name + "\"");
    }
    return sprites[name].get();
  }
}
