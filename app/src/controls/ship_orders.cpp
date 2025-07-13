#include "controls/ship_orders.hpp"

namespace controls {
  ShipOrders::ShipOrders(bool left, bool right, bool ahead, bool back)
  :
  left(left),
  right(right),
  ahead(ahead),
  back(back) {}

}
