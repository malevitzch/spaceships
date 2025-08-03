#ifndef ANGLE_HPP
#define ANGLE_HPP

namespace util {
  double mathfmod(const double value, const double modulus);

  // Angles are measured in radians
  class Angle {
  private:
    double val = 0;
  public:
    Angle();
    Angle(double value);

    Angle operator+(const Angle angle) const;
    Angle operator+(const double value) const;
    Angle operator-(const Angle angle) const;
    Angle operator-(const double value) const;

    Angle& operator+=(const Angle angle);
    Angle& operator+=(const double value);
    Angle& operator-=(const Angle angle);
    Angle& operator-=(const double value);

    double get() const;

    operator double() const;
    double getDegrees();
  };

  Angle degrees(double degrees);
}

#endif
