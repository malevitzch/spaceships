#include "core/objects/simple_projectile.hpp"
#include "assets/sprite_manager.hpp"
#include "assets/texture_manager.hpp"

namespace core {

  SimpleProjectile::SimpleProjectile(std::string sprite_name,
                                     util::Vec2d position,
                                     util::Vec2d velocity,
                                     util::Vec2d acceleration,
                                     double max_duration) 
  : max_duration(max_duration) {
    // TODO: maybe this should use some PhysicsObject constructor
    setPosition(position);
    setVelocity(velocity);
    setAcceleration(acceleration);


    // FIXME: use a sprite manager to just seamlessly get a sprite
    texture = assets::TextureManager::getShipTexture("BasicShip");
    sprite = std::make_unique<sf::Sprite>(*texture.lock());
  }

  void SimpleProjectile::physicsTick(double dt) {
    cur_duration += dt;
    if(cur_duration > max_duration) {
      expired = true;
    } else {
      PhysicsObject::physicsTick(dt);
    }
  }

  bool SimpleProjectile::isDestroyed() {
    return expired;
  }

  void SimpleProjectile::draw(sf::RenderTarget& target,
                              sf::RenderStates states) const {
    target.draw(*sprite, states);
  }
}
