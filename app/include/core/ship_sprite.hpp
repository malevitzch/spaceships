#ifndef CORE_SHIP_SPRITE_HPP
#define CORE_SHIP_SPRITE_HPP

#include "utility/vec2d.hpp"
#include <SFML/Graphics.hpp>

namespace core {
  class ShipSprite {
  private:
    std::shared_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite> sprite;
    util::Vec2d center_of_mass;
    util::Vec2d center_of_sprite;

    util::Vec2d sprite_size;
    double scale;
  public:
    ShipSprite(std::string name,
               util::Vec2d center_of_mass,
               util::Vec2d center_of_sprite,
               util::Vec2d sprite_size,
               double scale);
    sf::Sprite& getSprite();
  };
};

#endif
