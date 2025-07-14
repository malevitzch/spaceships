#ifndef CORE_SHIP_HPP
#define CORE_SHIP_HPP

#include "parts.hpp"
#include "parts/cores/spaceship_core.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <memory>

namespace core {
  class Ship : sf::Drawable {
  private:
    std::string name;
    std::shared_ptr<parts::SpaceshipCore> core;
  protected:
    std::shared_ptr<sf::Sprite> sprite;
  public:
    Ship(std::string name,
         std::shared_ptr<parts::SpaceshipCore> core,
         std::string texture_name);
    std::shared_ptr<parts::SpaceshipCore> getCore() const;

    // This sets the origin of the sprite properly
    virtual void setupSprite();
    // TODO: drawCentered for all sorts of displays,
    // where (center of sprite != center of mass)
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
  };
}

#endif
