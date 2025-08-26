#include "controls/ship_orders.hpp"

namespace controls {
  // FIXME: update with persistent behavior
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

    orders.mouse_left = mouse_left;
    orders.mouse_right = mouse_right;
    orders.mouse_middle = mouse_middle;

    return orders;
  }
}
