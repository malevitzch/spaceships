#include "core/objects/simple_projectile.hpp"
#include "assets/sprite_manager.hpp"

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

    sprite = assets::SpriteManager::getProjectileSprite(sprite_name);
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
