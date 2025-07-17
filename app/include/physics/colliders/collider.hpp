#ifndef PHYSICS_COLLIDERS_COLLIDER_HPP
#define PHYSICS_COLLIDERS_COLLIDER_HPP

#include "utility/angle.hpp"
#include "utility/vec2d.hpp"

namespace physics {
  namespace colliders {
    class Collider {
    private:
      util::Angle offset_angle;
      double offset_distance;
    public:
      util::Vec2d getPosition(util::Vec2d origin_pos,
                                    util::Angle origin_angle);

      // Returns the collider "radius" which is an approximation
      // of the maximum distane it can reach from origin
      // Especially important for composite colliders since it will allow
      // skipping computationally expensive check
      virtual double getRadius() = 0;

      // TODO: a better heuristic which takes into account true distance
      // from the origin and calculates the real origin as a sum of that + radius
      // virtual double getRadius(util::Vec2d center_distance);
      virtual bool collidesWith(Collider& collider,
                                util::Vec2d my_origin_pos,
                                util::Vec2d other_origin_pos,
                                util::Angle my_origin_angle,
                                util::Angle other_origin_angle) = 0;
    };
  }

}
#endif 
