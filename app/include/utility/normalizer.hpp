#ifndef UTILITY_NORMALIZER_HPP
#define UTILITY_NORMALIZER_HPP

namespace util {
  template <typename T, typename V>
  void normalize(T& object,
                 V (T::*check)() const,
                 void (T::*under)(),
                 void (T::*over)(),
                 void (T::*base)());
}

#include "normalizer.tpp"
#endif
