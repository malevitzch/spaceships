#ifndef CORE_SHIP_SPRITE_HPP
#define CORE_SHIP_SPRITE_HPP

#include "utility/vec2d.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace core {
  class ShipSprite : public sf::Drawable {
  private:
    std::shared_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite> sprite;
    util::Vec2d center_of_mass;

    util::Vec2d sprite_size;
    double scale;
  public:
    ShipSprite() = default;
    ShipSprite(std::string name,
               util::Vec2d sprite_size,
               util::Vec2d center_of_mass,
               double scale);
    sf::Sprite& getSprite();
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
    // The sprite given by this is not guaranteed to work
    // after the original exture holder is destroyed
    sf::Sprite getImageSprite() const;
  };
}

#endif
