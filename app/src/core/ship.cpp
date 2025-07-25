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
    texture =
      assets::TextureManager::getShipTexture(texture_name);
    sprite = std::make_shared<sf::Sprite>(*texture);
    setupSprite();
  }

  parts::SpaceshipCore& Ship::getCore() const { return *core; }
  util::Vec2d Ship::getPosition() const {
    return getCore().getPosition();
  }
  util::Angle Ship::getAngle() const {
    return getCore().getAngle();
  }

  std::string Ship::getName() const { return name; }

  void Ship::setupSprite() {
    sprite->setOrigin({25, 25});
  }

  void Ship::draw(sf::RenderTarget& target,
                  sf::RenderStates states) const {
    target.draw(*sprite, states);
  }
}
