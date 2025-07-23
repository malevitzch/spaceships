#ifndef CORE_CAMERA_HPP
#define CORE_CAMERA_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "utility/vec2d.hpp"
#include "core/ship_actor.hpp"
#include <vector>

namespace core {
  class Camera {
  protected:
    // Camera pos is in-game camera position
    // not the pixel position
    util::Vec2d camera_pos = {0, 0};
    util::Vec2d origin = {500, 500};
    sf::RenderWindow& target;
  public:
    Camera(sf::RenderWindow& target);

    // This translates in-game position to pixel-wise positioning
    util::Vec2d toPixelPosition(util::Vec2d pos);
    // Position -> position relative to camera 
    util::Vec2d toRelativePosition(util::Vec2d pos);
    // Position -> position on camera screen, relative to the center
    util::Vec2d translatePosition(util::Vec2d pos);

    void drawShips(std::vector<ShipActor> ships);
  };
}

#endif
