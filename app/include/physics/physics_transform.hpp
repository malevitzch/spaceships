#ifndef PHYSICS_TRANSFORM_HPP
#define PHYSICS_TRANSFORM_HPP

#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>

namespace physics {
  class PhysicsTransform {
  private:
    sf::Vector2<double> position = {0, 0};
    sf::Vector2<double> velocity = {0, 0};
    sf::Vector2<double> acceleration = {0, 0};

    // All angles are in radians
    double angle = 0;
    double angular_velocity = 0;
    double angular_acceleration = 0;
  public:
    PhysicsTransform() = default;
    PhysicsTransform(
      sf::Vector2<double> position,
      sf::Vector2<double> velocity,
      sf::Vector2<double> acceleration,
      double angle,
      double angular_velocity,
      double angular_acceleration);

    sf::Vector2<double> getPosition();
    sf::Vector2<double> getVelocity();
    sf::Vector2<double> getAcceleration();

    double getAngle();
    double getAngularVelocity();
    double getAngularAcceleration();

    void tick(double dt);
  };
}

#endif
