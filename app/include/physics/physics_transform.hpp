#ifndef PHYSICS_TRANSFORM_HPP
#define PHYSICS_TRANSFORM_HPP

#include <SFML/System/Angle.hpp>
#include "utility/vec2d.hpp"
#include "utility/angle.hpp"

namespace physics {
  struct PhysicsTransform {
    util::Vec2d position = {0, 0};
    util::Vec2d velocity = {0, 0};
    util::Vec2d acceleration = {0, 0};

    // All angles are in radians
    util::Angle angle = 0;
    double angular_velocity = 0;
    double angular_acceleration = 0;
    PhysicsTransform() = default;

    PhysicsTransform(
      util::Vec2d position,
      util::Vec2d velocity,
      util::Vec2d acceleration,
      util::Angle angle,
      double angular_velocity,
      double angular_acceleration);

      virtual void tick(double dt);
  };
}

#endif
