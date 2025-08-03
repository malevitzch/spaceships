#ifndef VEC2D
#define VEC2D

#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "angle.hpp"

namespace util {
  struct Vec2d {
    double x, y;

    Vec2d() = default;
    Vec2d(double x, double y);
    Vec2d(double magnitude, Angle angle);
    Vec2d(sf::Vector2f vec);
    Vec2d(sf::Vector2i vec);

    Vec2d operator-() const;

    Vec2d operator+(const Vec2d& vec) const;
    Vec2d operator+(const double scalar) const;

    Vec2d operator-(const Vec2d& vec) const;
    Vec2d operator-(const double scalar) const;

    Vec2d operator*(const double scalar) const;
    Vec2d operator/(const double scalar) const;

    Vec2d& operator+=(const Vec2d& vec);
    Vec2d& operator+=(const double scalar);

    Vec2d& operator-=(const Vec2d& vec);
    Vec2d& operator-=(const double scalar);

    Vec2d& operator*=(const double scalar);
    Vec2d& operator/=(const double scalar);

    double operator*(const Vec2d& vec) const;

    operator sf::Vector2f() const; 

    double magnitude() const;

    Vec2d unit() const;

    Vec2d rescale(const double length);
    Vec2d rescaled(const double length) const;
    Vec2d normalize();
    Vec2d normalized() const;

    double scalarProjection(Vec2d& vec);
    Vec2d vectorProjection(Vec2d& vec);

    static Vec2d zero();
    static Vec2d unit(Angle angle);
    static Vec2d unitX();
    static Vec2d unitY();

  };
  Vec2d operator*(const double scalar, const Vec2d& vec);

  std::ostream& operator<<(std::ostream& o, const Vec2d vec);

  Vec2d vecBetween(Vec2d from, Vec2d to, double length);

  double distance(Vec2d v1, Vec2d v2);
}

#endif
