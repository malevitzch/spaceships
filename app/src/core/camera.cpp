#include "core/camera.hpp"
#include <iostream>
namespace core {
  using util::Vec2d;
  Camera::Camera(sf::RenderWindow& target) : target(target) {}

  Vec2d Camera::toPixelPosition(Vec2d pos) {
    return {pos.x, pos.y};
  }
  Vec2d Camera::toRelativePosition(Vec2d pos) {
    return pos - (camera_pos - origin);
  }
  Vec2d Camera::translatePosition(Vec2d pos) {
    return toPixelPosition(toRelativePosition(pos));
  }

  void Camera::drawShips(std::vector<ShipActor> ships) {
    for(ShipActor& ship_actor : ships) {
      auto& ship = ship_actor.ship;
      Vec2d ship_pos = ship->getPosition();
      // FIXME: use RenderStates transform
      // Remove most of the ShipActor draw code so that it only
      // Draws its sprite
      Vec2d pixel_pos = translatePosition(ship_pos);
      std::cout << pixel_pos << "\n";
      sf::RenderStates states;
      states.transform.translate(pixel_pos);
      states.transform.rotate(sf::radians(ship->getAngle()));

      target.draw(*ship, states);
    }
  }
}
