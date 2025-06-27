#ifndef VEC2D
#define VEC2D

#include <SFML/System/Vector2.hpp>

namespace util {
  struct Vec2d {
    double x, y;

    Vec2d(double x, double y);
    Vec2d(sf::Vector2f vec);

    Vec2d operator-() const;

    Vec2d operator+(const Vec2d& vec) const;
    Vec2d operator-(const Vec2d& vec) const;
    Vec2d operator*(const double scalar) const;
    Vec2d operator/(const double scalar) const;

    Vec2d& operator+=(const Vec2d& vec);
    Vec2d& operator-=(const Vec2d& vec);
    Vec2d& operator*=(const double scalar);
    Vec2d& operator/=(const double scalar);

    operator sf::Vector2f() const; 

    double magnitude() const;

  };
  Vec2d operator*(const double scalar, const Vec2d& vec);
}

#endif
