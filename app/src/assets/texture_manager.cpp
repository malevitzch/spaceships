#include "assets/texture_manager.hpp"
#include "assets/paths.hpp"
#include <filesystem>

#include "logs/logger.hpp"

namespace assets {
  std::unordered_map<
    std::string,
    std::shared_ptr<sf::Texture>> TextureManager::textures;
  std::weak_ptr<sf::Texture> TextureManager::getTexture(std::string name) {
    if(textures.contains(name)) {
      return textures[name];
    }
    auto texture = 
      std::make_shared<sf::Texture>();
    if(!texture->loadFromFile(paths::getAssetsPath() + "/graphics/" + name + ".png")) {
      logs::Logger::logError("Failed to load texture \"" + name + "\"");
      // FIXME: missing texture, return something that's very clearly not supposed 
      // to be seen, like minecraft's pink-black 2x2 checkerboard
    }
    textures[name] = texture;
    return texture;
  }
  std::weak_ptr<sf::Texture> TextureManager::getShipTexture(std::string name) {
    return getTexture("ships/" + name);
  }
  std::weak_ptr<sf::Texture> TextureManager::getProjectileTexture(std::string name) {
    return getTexture("projectiles/" + name);
  }
  std::weak_ptr<sf::Texture> TextureManager::getBackgroundTexture(std::string name) {
    return getTexture("backgrounds/" + name);
  }

  void TextureManager::reset() {
    textures.clear();
  }
}
