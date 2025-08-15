#ifndef CORE_SHIP_HPP
#define CORE_SHIP_HPP

#include "assets/object_sprite.hpp"
#include "parts/cores/ship_core.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <memory>

namespace core {
  class Ship : public sf::Drawable {
  private:
    std::string name;
    std::shared_ptr<parts::ShipCore> core;
  protected:
    std::shared_ptr<ObjectSprite> sprite;
  public:
    Ship(std::string name,
         std::shared_ptr<parts::ShipCore> core,
         std::string sprite_name);

    parts::ShipCore& getCore() const;
    util::Vec2d getPosition() const;
    util::Angle getAngle() const;

    std::string getName() const;
    ObjectSprite& getSprite();
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
  };
}

#endif
