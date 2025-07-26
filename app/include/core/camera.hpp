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
    std::vector<std::shared_ptr<sf::Texture>> space_tx;
    std::vector<sf::Sprite> backgrounds;
  public:
    Camera(sf::RenderWindow& target);

    void moveTowards(util::Vec2d target, double dt);

    // This translates in-game position to pixel-wise positioning
    util::Vec2d toPixelPosition(util::Vec2d pos) const;
    // Position -> position relative to camera 
    util::Vec2d toRelativePosition(util::Vec2d pos) const;
    // Position -> position on camera screen, relative to the center
    util::Vec2d translatePosition(util::Vec2d pos) const;

    // Mathematical inverses of the functions above
    util::Vec2d inverseToPixelPosition(util::Vec2d pos) const;
    util::Vec2d inverseToRelativePosition(util::Vec2d pos) const;
    util::Vec2d inverseTranslatePosition(util::Vec2d pos) const;

    void drawShips(std::vector<ShipActor> ships);
    void drawBackground();
  };
}

#endif
