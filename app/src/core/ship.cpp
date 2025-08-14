#include "core/ship.hpp"
#include "assets/sprite_manager.hpp"
#include "assets/texture_manager.hpp"
#include "parts/cores/ship_core.hpp"
#include <memory>

namespace core {
  Ship::Ship(std::string name,
             std::shared_ptr<parts::ShipCore> core,
             std::string sprite_name) : name(name), core(core) {
    //FIXME: give a default texture in case of failure, don't cause
    // a null pointer dereference or an any other exception
    // and instead just return some silly missing ship texture
    sprite = assets::SpriteManager::getShipSprite(sprite_name); 
  }

  parts::ShipCore& Ship::getCore() const { return *core; }
  util::Vec2d Ship::getPosition() const {
    return getCore().getPosition();
  }
  util::Angle Ship::getAngle() const {
    return getCore().getAngle();
  }

  std::string Ship::getName() const { return name; }
  ShipSprite& Ship::getSprite() { return *sprite; }

  void Ship::draw(sf::RenderTarget& target,
                  sf::RenderStates states) const {
    target.draw(*sprite, states);
  }
}
