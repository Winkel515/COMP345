#ifndef Orders_H
#define Orders_H
#include <iostream>
#include <string>
#include <vector>

class Order {
 public:
  enum OrderType { Deploy, Advance, Bomb, Blockade, Airlift, Negotiate };
  Order();
  Order(Order::OrderType type);
  Order(const Order &o);
  Order &operator=(const Order &copy);
  ~Order();
  friend std::ostream &operator<<(std::ostream &output, const Order &o);
  void validate();
  void execute();
  void SetType(Order::OrderType type);
  Order::OrderType GetType() const;

 private:
  Order::OrderType TypeOfOrder;
  std::string orderEffect;
};

class OrdersList {
 public:
  OrdersList();
  OrdersList(const OrdersList &ordersList);
  ~OrdersList();
  OrdersList &operator=(const OrdersList &ordersList);
  void move(int initial, int final);
  void remove(int index);
  void add(Order *order);
  friend std::ostream &operator<<(std::ostream &o, const OrdersList &oL);
  void executeOrders();

 private:
  std::vector<Order *> ListOfOrders;
};

#endif