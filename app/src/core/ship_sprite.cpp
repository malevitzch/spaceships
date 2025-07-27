#include "core/ship_sprite.hpp"
#include "assets/texture_manager.hpp"

namespace core {
  using util::Vec2d;
  ShipSprite::ShipSprite(std::string name,
                         Vec2d sprite_size,
                         Vec2d center_of_mass,
                         Vec2d center_of_sprite,
                         double scale) :
                           center_of_mass(center_of_mass),
                           center_of_sprite(center_of_sprite) {
    texture = assets::TextureManager::getShipTexture(name);
    sprite = std::make_unique<sf::Sprite>(*texture);
  }
  sf::Sprite& ShipSprite::getSprite() {
    return *sprite;
  }
}
