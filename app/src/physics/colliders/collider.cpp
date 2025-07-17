#include "physics/colliders/collider.hpp"

namespace physics {
  namespace colliders {
    using util::Vec2d, util::Angle;
    Angle Collider::getAngle(Vec2d origin_pos, Angle origin_angle) {
      return offset_angle + origin_angle;
    }
    Vec2d Collider::getPosition(Vec2d origin_pos, Angle origin_angle) {
      return origin_pos + Vec2d(offset_distance, origin_angle + offset_angle);
    }
  }
}
