#include "physics/colliders/sphere_collider.hpp"

namespace physics {
  namespace colliders {
    using util::Angle, util::Vec2d;
    double SphereCollider::getRadius() {return radius;}
    bool SphereCollider::collidesWith(Collider& collider,
                                      Vec2d my_origin_pos,
                                      Vec2d other_origin_pos,
                                      Angle my_origin_angle,
                                      Angle other_origin_angle) {
      return collider.collidesWith(*this,
                                   other_origin_pos,
                                   my_origin_pos,
                                   other_origin_angle,
                                   my_origin_angle);
    }
    bool SphereCollider::collidesWithSphere(SphereCollider& sphere,
                                            Vec2d my_origin_pos,
                                            Vec2d other_origin_pos,
                                            Angle my_origin_angle,
                                            Angle other_origin_angle) {
      Vec2d my_pos = getPosition(my_origin_pos, my_origin_angle);
      Vec2d other_pos = sphere.getPosition(other_origin_pos, other_origin_angle);
      return (my_pos - other_pos).magnitude() <= radius + sphere.radius;
    }
  }
}
