#include "assets/sprite_manager.hpp"
#include "assets/paths.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <stdexcept>

namespace assets {
  std::map<std::string,
           SpriteManager::SpriteInfo> SpriteManager::ship_sprites;
  std::map<std::string,
           SpriteManager::SpriteInfo> SpriteManager::projectile_sprites;

  std::shared_ptr<core::ObjectSprite> SpriteManager::SpriteInfo::get() {
    if(sprite == nullptr) {
      sprite = std::make_shared<core::ObjectSprite>(texture_name,
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
    if(!spritestream) {
      // TODO: error handling
      return;
    }
    json data = json::parse(spritestream);
    for(auto& sprite_data : data["sprites"]) {
      ship_sprites[sprite_data["name"]] = {
        sprite_data["filename"],
        {sprite_data["size"]["x"], sprite_data["size"]["y"]},
        {sprite_data["origin"]["x"], sprite_data["origin"]["y"]},
        sprite_data["scale"]
      };
    }
  }

  void SpriteManager::loadProjectileSprites() {
    using nlohmann::json;
    std::ifstream spritestream(
      assets::paths::getAssetsPath() + "/json/projectile_sprites.json");
    if(!spritestream) {
      // TODO: error handling
      return;
    }
    json data = json::parse(spritestream);
    for(auto& sprite_data : data["sprites"]) {
      projectile_sprites[sprite_data["name"]] = {
        sprite_data["filename"],
        {sprite_data["size"]["x"], sprite_data["size"]["y"]},
        {sprite_data["origin"]["x"], sprite_data["origin"]["y"]},
        sprite_data["scale"]
      };
    }
  }

  std::shared_ptr<core::ObjectSprite> SpriteManager::getShipSprite(
    std::string name) {
    if(!ship_sprites.contains(name)) {
      throw std::runtime_error("Unknown sprite name: \"" + name + "\"");
    }
    return ship_sprites[name].get();
  }

  std::shared_ptr<core::ObjectSprite> SpriteManager::getProjectileSprite(
    std::string name) {
    if(!projectile_sprites.contains(name)) {
      throw std::runtime_error("Unknown sprite name: \"" + name + "\"");
    }
    return projectile_sprites[name].get();
  }
}
