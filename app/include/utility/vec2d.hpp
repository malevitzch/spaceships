#ifndef VEC2D
#define VEC2D

#include <SFML/System/Vector2.hpp>

#include "angle.hpp"

namespace util {
  struct Vec2d {
    double x, y;

    Vec2d(double x, double y);
    Vec2d(double magnitude, Angle angle);
    Vec2d(sf::Vector2f vec);

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

    Vec2d& rescale(const double length);

    double scalarProjection(Vec2d& vec);
    Vec2d vectorProjection(Vec2d& vec);

    static Vec2d zero();
    static Vec2d unit(Angle angle);
    static Vec2d unitX();
    static Vec2d unitY();

  };
  Vec2d operator*(const double scalar, const Vec2d& vec);
}

#endif
