#include "core/camera.hpp"
#include "assets/texture_manager.hpp"
#include <cmath>
#include <string>
namespace core {
  using util::Vec2d;
  Camera::Camera(sf::RenderWindow& target) : target(target) {
    static const int backgroundCount = 6;
    for(int i = 0; i < backgroundCount; i++) {
      space_tx.push_back(assets::TextureManager::getBackgroundTexture(
        "starfield0" + std::to_string(i+1)));
    }
    for(int i = 0; i < backgroundCount; i++) {
      backgrounds.push_back(sf::Sprite(*space_tx[i].lock()));
    }
  }

  util::Vec2d Camera::getPosition() const { return camera_pos; }
  void Camera::setPosition(Vec2d target) {
    camera_pos = target;
  }
  void Camera::moveTowards(Vec2d target, double dt) {
    double dist = util::distance(camera_pos, target);
    if(dist > 10) camera_pos += util::vecBetween(camera_pos, target, dt * std::pow(dist, 1.6) / 3);
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
  Vec2d Camera::inverseToPixelPosition(util::Vec2d pos) const {
    return pos - origin;
  }
  Vec2d Camera::inverseToRelativePosition(Vec2d pos) const {
    return pos + camera_pos;
  }
  Vec2d Camera::inverseTranslatePosition(Vec2d pos) const {
    return inverseToRelativePosition(inverseToPixelPosition(pos));
  }

  void Camera::drawShips(std::vector<ShipActor> ships) {
    for(ShipActor& ship_actor : ships) {
      auto& ship = ship_actor.getShip();
      Vec2d ship_pos = ship.getPosition();

      Vec2d pixel_pos = translatePosition(ship_pos);

      sf::RenderStates states;
      states.transform.translate(pixel_pos);
      states.transform.rotate(sf::radians(ship.getAngle()));

      target.draw(ship, states);
    }
  }

  void Camera::drawBackground() {
    double x = util::mathfmod(camera_pos.x, 1000);
    double y = util::mathfmod(camera_pos.y, 1000);

    long long x_bg = (camera_pos.x - x) / 1000; 
    long long y_bg = (camera_pos.y - y) / 1000;

    for(int i = -1; i <= 1; i++) {
      for(int j = -1; j <= 1; j++) {
        sf::RenderStates states;
        states.transform.translate(Vec2d(i * 1000.0 - x, j * 1000.0 - y));
        auto& sprite = backgrounds[labs((x_bg + i) * 11 + (y_bg + j) * 7) % 2];
        target.draw(sprite, states);
      }
    }
  }
}
