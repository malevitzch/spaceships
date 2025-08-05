#include "controls/ship_orders.hpp"

namespace controls {
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
