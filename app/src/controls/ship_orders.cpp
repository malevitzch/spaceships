#include "controls/ship_orders.hpp"

namespace controls {
  // FIXME: I honestly don't really care for this constructor
  // it's kinda useless since the struct is too big
  ShipOrders::ShipOrders(bool left, bool right, bool ahead, bool back)
  :
  left(left),
  right(right),
  ahead(ahead),
  back(back) {}

  ShipOrders ShipOrders::prolong() const {
    ShipOrders orders;

    orders.left = left;
    orders.right = right;
    orders.ahead = ahead;
    orders.back = back;

    orders.left_arrow = left_arrow;
    orders.right_arrow = right_arrow;
    orders.up_arrow = up_arrow;
    orders.down_arrow = down_arrow;

    return orders;
  }
}
