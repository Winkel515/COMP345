#ifndef Orders_H
#define Orders_H
#include <iostream>
#include <string>
#include <vector>
#include "LoggingObserver.h"

class Order : public Subject, public ILoggable{
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
  std::string GetType() const;
  void stringToLog();

 private:
  Order::OrderType TypeOfOrder;
  std::string orderEffect;
};

class OrdersList : public Subject, public ILoggable{
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
  void stringToLog();

 private:
  std::vector<Order *> ListOfOrders;
};

#endif