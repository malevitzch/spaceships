#include "assets/object_sprite.hpp"
#include "assets/texture_manager.hpp"

namespace assets {
  using util::Vec2d;
  ObjectSprite::ObjectSprite(std::string name,
                             Vec2d sprite_size,
                             Vec2d center_of_mass,
                             double scale,
                             std::weak_ptr<sf::Texture> texture) :
                           center_of_mass(center_of_mass),
                           sprite_size(sprite_size),
                           scale(scale),
                           texture(texture) {
    sprite = std::make_unique<sf::Sprite>(*texture.lock());

    sprite->setScale(util::Vec2d(scale, scale));
    sprite->setOrigin(center_of_mass);
  }
  sf::Sprite& ObjectSprite::getSprite() {
    return *sprite;
  }
  void ObjectSprite::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
    target.draw(*sprite, states);
  }
  sf::Sprite ObjectSprite::getImageSprite() const {
    sf::Sprite sprite(*texture.lock());
    sprite.setScale(util::Vec2d(scale, scale));

    sprite.setRotation(sf::degrees(-90));

    sprite.setOrigin(sprite_size / 2);
    return sprite;
  }

  ShipSprite::ShipSprite(std::string name,
                         util::Vec2d sprite_size,
                         util::Vec2d center_of_mass,
                         double scale)
  : ObjectSprite(name,
                 sprite_size,
                 center_of_mass,
                 scale,
                 assets::TextureManager::getShipTexture(name)) {}

  ProjectileSprite::ProjectileSprite(std::string name,
                                     util::Vec2d sprite_size,
                                     util::Vec2d center_of_mass,
                                     double scale)
  : ObjectSprite(name,
                 sprite_size,
                 center_of_mass,
                 scale,
                 assets::TextureManager::getProjectileTexture(name)) {}
}
