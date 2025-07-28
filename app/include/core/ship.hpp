#ifndef CORE_SHIP_HPP
#define CORE_SHIP_HPP

#include "core/ship_sprite.hpp"
#include "parts.hpp"
#include "parts/cores/spaceship_core.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <memory>

namespace core {
  class Ship : public sf::Drawable {
  private:
    std::string name;
    std::shared_ptr<parts::SpaceshipCore> core;
  protected:
    std::shared_ptr<ShipSprite> sprite;
  public:
    Ship(std::string name,
         std::shared_ptr<parts::SpaceshipCore> core,
         std::string sprite_name);

    parts::SpaceshipCore& getCore() const;
    util::Vec2d getPosition() const;
    util::Angle getAngle() const;

    std::string getName() const;
    // This sets the origin of the sprite properly
    // TODO: drawCentered for all sorts of displays,
    // where (center of sprite != center of mass)
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
  };
}

#endif
