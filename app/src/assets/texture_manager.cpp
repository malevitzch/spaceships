#include "assets/texture_manager.hpp"

namespace assets {
  std::unordered_map<std::string, std::weak_ptr<sf::Texture>> TextureManager::textures;
  std::shared_ptr<sf::Texture> TextureManager::getTexture(std::string name) {
    if(textures.contains(name)) {
      if(auto texture = textures[name].lock()) {
        return texture;
      }
    }
    auto texture = std::make_shared<sf::Texture>("assets/graphics/" + name + ".png");
    textures[name] = texture;
    return texture;
  }
}
