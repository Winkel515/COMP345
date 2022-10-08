#include "OrdersDriver.h"

#include <iostream>

#include "Orders.h"

// Test Orders class
void testOrdersList() {
  OrdersList testList;

  testList.add(new Order(Order::Deploy));
  testList.add(new Order(Order::Advance));
  testList.add(new Order(Order::Bomb));
  testList.add(new Order(Order::Blockade));
  testList.add(new Order(Order::Airlift));
  testList.add(new Order(Order::Negotiate));

  std::cout << testList;

  testList.move(0, 5);

  std::cout << testList;

  testList.remove(2);

  std::cout << testList;

  testList.executeOrders();
}