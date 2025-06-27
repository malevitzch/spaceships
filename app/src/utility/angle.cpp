#include "utility/angle.hpp"
#include <cmath>
#include <numbers>

namespace util {

  constexpr double twopi = std::numbers::pi * 2;

  double mathfmod(const double value, const double modulus) {
    return std::fmod(std::fmod(value, modulus) + modulus, modulus);
  }

  Angle::Angle() : val(0) {}
  Angle::Angle(double value) : val(mathfmod(value, twopi)) {}

  Angle Angle::operator+(const Angle angle) const {
    return Angle(this->val + angle.get());
  }
  Angle Angle::operator+(const double value) const {
    return Angle(this->val + value);
  }
  Angle Angle::operator-(const Angle angle) const {
    return Angle(this->val - angle.get());
  }
  Angle Angle::operator-(const double value) const {
    return Angle(this->val - value);
  }

  Angle& Angle::operator+=(const Angle angle) {
    this->val += mathfmod(this->val + angle.get(), twopi);
    return *this;
  }
  Angle& Angle::operator+=(const double value) {
    this->val = mathfmod(this->val + value, twopi);
    return *this;
  }
  Angle& Angle::operator-=(const Angle angle) {
    this->val += mathfmod(this->val - angle.get(), twopi);
    return *this;
  }
  Angle& Angle::operator-=(const double value) {
    this->val = mathfmod(this->val - value, twopi);
    return *this;
  }

  double Angle::get() const {
    return val;
  }

  Angle::operator double() const {
    return get();
  }
}
