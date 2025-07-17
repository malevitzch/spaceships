#ifndef PHYSICS_COLLIDERS_SPHERE_COLLIDER_HPP
#define PHYSICS_COLLIDERS_SPHERE_COLLIDER_HPP

#include "physics/colliders/collider.hpp"

namespace physics {
  namespace colliders {
    class SphereCollider : public Collider {
    private:
      double radius;
    public:
      virtual double getRadius() override;
      virtual bool collidesWith(Collider& collider,
                                util::Vec2d my_origin_pos,
                                util::Vec2d other_origin_pos,
                                util::Angle my_origin_angle,
                                util::Angle other_origin_angle) override;
      virtual bool collidesWithSphere(
                                SphereCollider& sphere,
                                util::Vec2d my_origin_pos,
                                util::Vec2d other_origin_pos,
                                util::Angle my_origin_angle,
                                util::Angle other_origin_angle) override;
    };
  }
}
#endif
