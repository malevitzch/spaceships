#include "utility/vec2d.hpp"
#include <cmath>

namespace util {
  Vec2d::Vec2d(double x, double y) : x(x), y(y) {}

  Vec2d::Vec2d(double magnitude, Angle angle)
  : x(magnitude * cos(angle)), y(magnitude * sin(angle)) {}

  Vec2d::Vec2d(sf::Vector2f vec) : x(vec.x), y(vec.y) {}

  Vec2d Vec2d::operator-() const {
    return (*this) * -1;
  }

  Vec2d Vec2d::operator+(const Vec2d& vec) const {
    return Vec2d(this->x + vec.x, this->y + vec.y);
  }
  Vec2d Vec2d::operator+(const double scalar) const {
    return Vec2d(this->x + scalar, this->y + scalar);
  }
  Vec2d Vec2d::operator-(const Vec2d& vec) const {
    return Vec2d(this->x - vec.x, this->y - vec.y);
  }
  Vec2d Vec2d::operator-(const double scalar) const {
    return Vec2d(this->x - scalar, this->y - scalar);
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
  Vec2d& Vec2d::operator+=(const double scalar) {
    this->x += scalar;
    this->y += scalar;
    return *this;
  }
  Vec2d& Vec2d::operator-=(const Vec2d& vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
  }
  Vec2d& Vec2d::operator-=(const double scalar) {
    this->x -= scalar;
    this->y -= scalar;
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

  double Vec2d::operator*(const Vec2d& vec) const {
    return (x * vec.x) + (y * vec.y);
  }

  Vec2d::operator sf::Vector2f() const {
    return sf::Vector2f(float(x), float(y));
  }

  double Vec2d::magnitude() const {
    return std::sqrt(x*x + y*y);
  }

  Vec2d Vec2d::unit() const {
    double length = magnitude();
    // This is reasonable behavior to avoid division by 0
    if(length == 0) {
      return {0, 0};
    }
    return Vec2d(*this) / length;
  }

  Vec2d& Vec2d::rescale(const double length) {
    if(magnitude() == 0) {
      return *this;
    }
    (*this) *= (length / magnitude());
    return *this;
  }

  Vec2d Vec2d::zero() {
    return {0, 0};
  }
  Vec2d Vec2d::unitX() {
    return Vec2d(1, 0);
  }

  Vec2d Vec2d::unitY() {
    return Vec2d(0, 1);
  }

  Vec2d Vec2d::unit(Angle angle) {
    return Vec2d(1, angle);
  }

  double Vec2d::scalarProjection(Vec2d& vec) {
    double veclength = vec.magnitude();
    if(veclength == 0) {
      return 0;
    }
    return ((*this) * vec) / veclength;
  }
  Vec2d Vec2d::vectorProjection(Vec2d& vec) {
    return vec * scalarProjection(vec);
  }

  Vec2d operator*(const double scalar, const Vec2d& vec) {
    return Vec2d(vec.x * scalar, vec.y * scalar);
  }

  double distance(Vec2d v1, Vec2d v2) {
    return (v1 - v2).magnitude();
  }
}
