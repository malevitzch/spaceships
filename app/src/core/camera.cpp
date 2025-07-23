#include "core/camera.hpp"

namespace core {
  using util::Vec2d;
  Camera::Camera(sf::RenderWindow& target) : target(target) {}

  Vec2d Camera::translatePosition(Vec2d pos) {
    return {pos.x, -pos.y};
  }
  Vec2d Camera::toRelativePosition(Vec2d pos) {
    return camera_pos - pos;
  }
}
