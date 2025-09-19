#ifndef CORE_OBJECTS_SIMPLE_PROJECTILE_HPP
#define CORE_OBJECTS_SIMPLE_PROJECTILE_HPP

#include "assets/object_sprite.hpp"
#include "core/objects/projectile.hpp"
#include "utility/angle.hpp"
#include "utility/vec2d.hpp"

namespace core {
  class SimpleProjectile : public Projectile {
  private:
    const double max_duration;
    double cur_duration = 0;
    bool expired = false;
    std::shared_ptr<assets::ObjectSprite> sprite;
  public:
    SimpleProjectile(std::string sprite_name,
                     util::Vec2d position,
                     util::Vec2d velocity,
                     util::Vec2d acceleration,
                     util::Angle angle,
                     double duration);
    virtual void physicsTick(double dt) override;
    virtual bool isDestroyed() override;
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
  };
}

#endif
