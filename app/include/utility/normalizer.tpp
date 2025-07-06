
namespace util {
  template <typename T, typename V>
  void normalize(T& object,
                 V (T::*check)() const,
                 void (T::*under)(),
                 void (T::*over)(),
                 void (T::*base)()) {
    V val = (object.*check)();
    V def = V{};
    if(val < def) {
      (object.*under)();
    } else if (val > def) {
      (object.*over)();
    } else {
      (object.*base)();
    }
  }
}
