#include "core/ship.hpp"
#include "assets/texture_manager.hpp"
#include "parts/cores/spaceship_core.hpp"
#include <memory>

namespace core {
  Ship::Ship(std::string name,
             std::shared_ptr<parts::SpaceshipCore> core,
             std::string texture_name) : name(name), core(core) {
    //FIXME: give a default texture in case of failure, don't cause
    // a null pointer dereference or an any other exception
    // and instead just return some silly missing ship texture
    std::shared_ptr<sf::Texture> texture =
      assets::TextureManager::getTexture(texture_name);
    sprite = std::make_shared<sf::Sprite>(*texture);
    setupSprite();
  }
  std::shared_ptr<parts::SpaceshipCore> Ship::getCore() const {
    return core;
  }
  void Ship::setupSprite() {
    sprite->setOrigin({25, 25});
  }
}
