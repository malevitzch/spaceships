#ifndef CORE_OBJECTS_SIMPLE_PROJECTILE_HPP
#define CORE_OBJECTS_SIMPLE_PROJECTILE_HPP

#include "core/objects/space_object.hpp"
#include "utility/vec2d.hpp"

namespace core {
  class SimpleProjectile : public SpaceObject {
  private:
    const double max_duration;
    double cur_duration = 0;
    bool expired = false;
    std::weak_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite> sprite = nullptr;
  public:
    SimpleProjectile(std::string sprite_name,
                     util::Vec2d position,
                     util::Vec2d velocity,
                     util::Vec2d acceleration,
                     double duration);
    virtual void physicsTick(double dt) override;
    virtual bool isDestroyed() override;
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
  };
}

#endif
