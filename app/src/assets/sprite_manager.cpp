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
    loadShipSprites("ship_sprites.json");

    loadProjectileSprites("projectile_sprites.json");
  }

  // TODO: this should have a filename as a parameter and just load from the file
  // rather than a single hardcoded one
  bool SpriteManager::loadShipSprites(std::string filename) {
    using nlohmann::json;

    std::ifstream spritestream(
      assets::paths::getAssetsPath() + "/json/" + filename);
    if(!spritestream) {
      logs::Logger::logError("Couldn't open file \"" + filename + "\"");
      return false;
    }

    json data;
    try {
      data = json::parse(spritestream);
    } catch(const json::parse_error& e) {
      logs::Logger::logError("Failed to parse JSON from "
                             "file \"" + filename + "\".");
      return false;
    }

    if(!data.contains("sprites")) {
      logs::Logger::logError("Attempting to load sprites from the file "
                             "\"" + filename + "\" but it contains "
                             "no \"sprites\" field.");
      return false;
    }

    for(auto& sprite_data : data["sprites"]) {
      // TODO: handle missing data here,
      // error if missing crucial things like filename
      // but give reasonable defaults for others
      ship_sprites[sprite_data["name"]] = {
        sprite_data["filename"],
        {sprite_data["size"]["x"], sprite_data["size"]["y"]},
        {sprite_data["origin"]["x"], sprite_data["origin"]["y"]},
        sprite_data["scale"],
        SpriteType::Ship
      };
    }

    logs::Logger::logInfo("Loaded ship sprites from " + filename);
    return true;
  }

  bool SpriteManager::loadProjectileSprites(std::string filename) {
    using nlohmann::json;

    std::ifstream spritestream(
      assets::paths::getAssetsPath() + "/json/" + filename);
    if(!spritestream) {
      logs::Logger::logError("Couldn't open file \"" + filename + "\"");
      return false;
    }

    json data;
    try {
      data = json::parse(spritestream);
    } catch(const json::parse_error& e) {
      logs::Logger::logError("Failed to parse JSON from "
                             "file \"" + filename + "\".");
      return false;
    }
    for(auto& sprite_data : data["sprites"]) {
      // TODO: error handle inside
      projectile_sprites[sprite_data["name"]] = {
        sprite_data["filename"],
        {sprite_data["size"]["x"], sprite_data["size"]["y"]},
        {sprite_data["origin"]["x"], sprite_data["origin"]["y"]},
        sprite_data["scale"],
        SpriteType::Projectile
      };
    }

    logs::Logger::logInfo("Loaded projectile sprites from " + filename);
    return true;
  }

  std::shared_ptr<ObjectSprite> SpriteManager::getShipSprite(
    std::string name) {
    if(!ship_sprites.contains(name)) {
      logs::Logger::logFatalAndDump("Unknown sprite name: \"" + name + "\"");
      // FIXME: return a silly placeholder sprite so that the game doesn't crash
    }
    return ship_sprites[name].get();
  }

  std::shared_ptr<ObjectSprite> SpriteManager::getProjectileSprite(
    std::string name) {
    if(!projectile_sprites.contains(name)) {
      logs::Logger::logFatalAndDump("Unknown sprite name: \"" + name + "\"");
      // FIXME: return a silly placeholder sprite so that the game doesn't crash
    }
    return projectile_sprites[name].get();
  }
}
