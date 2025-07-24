#include "core/camera.hpp"
#include "assets/texture_manager.hpp"
#include <cmath>
namespace core {
  using util::Vec2d;
  Camera::Camera(sf::RenderWindow& target) : target(target) {}

  void Camera::moveTowards(Vec2d target, double dt) {
    double dist = util::distance(camera_pos, target);
    camera_pos += util::vecBetween(camera_pos, target, dt * std::pow(dist, 1.6) / 3);
  }

  Vec2d Camera::toPixelPosition(Vec2d pos) const {
    return pos + origin;
  }
  Vec2d Camera::toRelativePosition(Vec2d pos) const {
    return pos - (camera_pos);
  }
  Vec2d Camera::translatePosition(Vec2d pos) const {
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
      sf::RenderStates states;
      states.transform.translate(pixel_pos);
      states.transform.rotate(sf::radians(ship->getAngle()));

      target.draw(*ship, states);
    }
  }

  void Camera::drawBackground() {
    double x = util::mathfmod(camera_pos.x, 1000);
    double y = util::mathfmod(camera_pos.y, 1000);

    sf::Sprite sprite(*assets::TextureManager::getBackgroundTexture("SpaceBackground"));

    for(int i = -1; i <= 1; i++) {
      for(int j = -1; j <= 1; j++) {
        sf::RenderStates states;
        states.transform.translate(Vec2d(i * 1000.0 - x, j * 1000.0 - y));
        target.draw(sprite, states);
      }
    }
  }
}
