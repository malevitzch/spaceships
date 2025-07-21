#include "assets/texture_manager.hpp"
#include "assets/paths.hpp"
#include <stdexcept>
#include <filesystem>

namespace assets {
  std::unordered_map<
    std::string,
    std::weak_ptr<sf::Texture>> TextureManager::textures;
  std::shared_ptr<sf::Texture> TextureManager::getTexture(std::string name) {
    if(textures.contains(name) && textures[name].lock()) {
      return textures[name].lock();
    }
    auto texture = 
      std::make_shared<sf::Texture>();
    if(!texture->loadFromFile(paths::getAssetsPath() + "/graphics/" + name + ".png")) {
      throw new std::runtime_error("Failed to load texture \"" + name + "\"");
    }
    textures[name] = texture;
    return texture;
  }
  std::shared_ptr<sf::Texture> TextureManager::getShipTexture(std::string name) {
    return getTexture("ships/" + name);
  }
  std::shared_ptr<sf::Texture> TextureManager::getBackgroundTexture(std::string name) {
    return getTexture("backgrounds/" + name);
  }
}
