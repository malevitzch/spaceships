#include "utility/vec2d.hpp"
#include <cmath>

namespace util {
  Vec2d::Vec2d(double x, double y) : x(x), y(y) {}
  Vec2d::Vec2d(sf::Vector2f vec) : x(vec.x), y(vec.y) {}

  Vec2d Vec2d::operator-() const {
    return (*this) * -1;
  }

  Vec2d Vec2d::operator+(const Vec2d& vec) const {
    return Vec2d(this->x + vec.x, this->y + vec.y);
  }
  Vec2d Vec2d::operator-(const Vec2d& vec) const {
    return Vec2d(this->x - vec.x, this->y - vec.y);
  }
  Vec2d Vec2d::operator*(const double scalar) const {
    return Vec2d(this->x * scalar, this->y * scalar);
  }
  Vec2d Vec2d::operator/(const double scalar) const {
    return Vec2d(this->x / scalar, this->y / scalar);
  }

  Vec2d& Vec2d::operator+=(const Vec2d& vec) {
    this->x += vec.x;
    this->y += vec.y;
    return *this;
  }
  Vec2d& Vec2d::operator-=(const Vec2d& vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
  }
  Vec2d& Vec2d::operator*=(const double scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  }
  Vec2d& Vec2d::operator/=(const double scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
  }

  Vec2d::operator sf::Vector2f() const {
    return sf::Vector2f(float(x), float(y));
  }

  double Vec2d::magnitude() const {
    return std::sqrt(x*x + y*y);
  }


  Vec2d operator*(const double scalar, const Vec2d& vec) {
    return Vec2d(vec.x * scalar, vec.y * scalar);
  }

}
