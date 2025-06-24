#ifndef PHYSICS_TRANSFORM_HPP
#define PHYSICS_TRANSFORM_HPP

#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>

namespace physics {
  class PhysicsTransform {
  private:
    sf::Vector2<double> position;
    sf::Vector2<double> velocity;
    sf::Vector2<double> acceleration;
    double angle;
    double angular_velocity; // In radians
    double angular_acceleration;
  public:
    sf::Vector2<double> getPosition();
    sf::Vector2<double> getVelocity();
    sf::Vector2<double> getAcceleration();
    double getAngle();
    double getAngularVelocity();
    double getAngularAcceleration();

    void update(double dt);
  };
}

#endif
