#include "assets/sprite_manager.hpp"
#include "assets/paths.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <stdexcept>

#include "logs/logger.hpp"

namespace assets {
  std::map<std::string,
           SpriteManager::SpriteInfo> SpriteManager::ship_sprites;
  std::map<std::string,
           SpriteManager::SpriteInfo> SpriteManager::projectile_sprites;

  std::shared_ptr<ObjectSprite> SpriteManager::SpriteInfo::get() {
    if(sprite == nullptr) {
      switch (type) {
        case SpriteType::Ship:
          sprite = std::make_shared<ShipSprite>(texture_name,
                                                center_of_mass,
                                                sprite_size,
                                                scale);
          break;
        case SpriteType::Projectile:
          sprite = std::make_shared<ProjectileSprite>(texture_name,
                                                      center_of_mass,
                                                      sprite_size,
                                                      scale);
          break;
        default:
          break;
      }
    }
    return sprite;
  }

  void SpriteManager::init() {
    loadShipSprites();
    logs::Logger::logInfo("Loaded ship sprites");

    loadProjectileSprites();
    logs::Logger::logInfo("Loaded projectile sprites");
  }

  // TODO: this should have a filename as a parameter and just load from the file
  // rather than a single hardcoded one
  void SpriteManager::loadShipSprites() {
    using nlohmann::json;
    std::ifstream spritestream(
      assets::paths::getAssetsPath() + "/json/ship_sprites.json");
    if(!spritestream) {
      logs::Logger::logError("Couldn't open file \"ship_sprites.json\"");
      return;
    }
    json data = json::parse(spritestream);
    //TODO: error handling
    for(auto& sprite_data : data["sprites"]) {
      ship_sprites[sprite_data["name"]] = {
        sprite_data["filename"],
        {sprite_data["size"]["x"], sprite_data["size"]["y"]},
        {sprite_data["origin"]["x"], sprite_data["origin"]["y"]},
        sprite_data["scale"],
        SpriteType::Ship
      };
    }
  }

  // TODO: parametrized file 
  void SpriteManager::loadProjectileSprites() {
    using nlohmann::json;
    std::ifstream spritestream(
      assets::paths::getAssetsPath() + "/json/projectile_sprites.json");
    if(!spritestream) {
      logs::Logger::logError("Couldn't open file \"projectile_sprites.json\"");
    }
    json data = json::parse(spritestream);
    // TODO: error handling
    for(auto& sprite_data : data["sprites"]) {
      projectile_sprites[sprite_data["name"]] = {
        sprite_data["filename"],
        {sprite_data["size"]["x"], sprite_data["size"]["y"]},
        {sprite_data["origin"]["x"], sprite_data["origin"]["y"]},
        sprite_data["scale"],
        SpriteType::Projectile
      };
    }
  }

  std::shared_ptr<ObjectSprite> SpriteManager::getShipSprite(
    std::string name) {
    if(!ship_sprites.contains(name)) {
      logs::Logger::logError("Unknown sprite name: \"" + name + "\"");
      // FIXME: return a silly placeholder sprite so that the game doesn't crash
    }
    return ship_sprites[name].get();
  }

  std::shared_ptr<ObjectSprite> SpriteManager::getProjectileSprite(
    std::string name) {
    if(!projectile_sprites.contains(name)) {
      logs::Logger::logError("Unknown sprite name: \"" + name + "\"");
      // FIXME: return a silly placeholder sprite so that the game doesn't crash
    }
    return projectile_sprites[name].get();
  }
}
