#ifndef ASSETS_TEXTURE_MANAGER_HPP
#define ASSETS_TEXTURE_MANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <string>
#include <memory>

namespace assets {
  class TextureManager {
  private:
    static std::unordered_map<std::string, std::weak_ptr<sf::Texture>> textures;
    static std::shared_ptr<sf::Texture> getTexture(std::string name);
  public:
    static std::shared_ptr<sf::Texture> getShipTexture(std::string name);
    static std::shared_ptr<sf::Texture> getBackgroundTexture(std::string name);
  };
}

#endif 
