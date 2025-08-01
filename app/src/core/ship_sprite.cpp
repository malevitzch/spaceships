#include "core/ship_sprite.hpp"
#include "assets/texture_manager.hpp"

namespace core {
  using util::Vec2d;
  ShipSprite::ShipSprite(std::string name,
                         Vec2d sprite_size,
                         Vec2d center_of_mass,
                         double scale) :
                           center_of_mass(center_of_mass),
                           sprite_size(sprite_size),
                           scale(scale) {
    texture = assets::TextureManager::getShipTexture(name);
    sprite = std::make_unique<sf::Sprite>(*texture);

    sprite->setScale(util::Vec2d(scale, scale));
    // TODO: investigate

    //sprite->setRotation(sf::degrees(-90));
    sprite->setOrigin(center_of_mass);
  }
  sf::Sprite& ShipSprite::getSprite() {
    return *sprite;
  }
  void ShipSprite::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
    target.draw(*sprite, states);
  }
  sf::Sprite ShipSprite::getImageSprite() const {
    sf::Sprite sprite(*texture);
    sprite.setScale(util::Vec2d(scale, scale));
    // TODO: investigate

    sprite.setRotation(sf::degrees(-90));

    sprite.setOrigin(sprite_size / 2);
    return sprite;
  }

}
