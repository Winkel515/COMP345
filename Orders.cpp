#include "Orders.h"

class Orders {
 public:
  string type;
  int units;
  int source;  // will change to node once territories are implemented
  int target;  // same here
  void validate();
  void execute();

  Orders(string type, int units, int source, int target) {
    type = type;
    units = units;
    source = source;
    target = target;
  };

 private:
};

class OrdersList {
 public:
  OrdersList(list<Orders> OrdersList);

  void move(list<Orders> OrdersList, int initial, int final) {
    // Declare 2 iterators at the begining of the list
    list<Orders>::iterator ptrInitial = OrdersList.begin();
    list<Orders>::iterator ptrFinal = OrdersList.begin();

    // Increment the iterators to the specified inital and final positions
    advance(ptrInitial, initial);
    advance(ptrFinal, final);

    // Move the elements with splice function
    OrdersList.splice(ptrFinal, OrdersList, ptrInitial);
  };

  void remove(list<Orders> OrdersList, Orders order) {
    OrdersList.remove(order);
  };

  void add(list<Orders> OrdersList, Orders order) {
    // Iterator at the end to add the order at the end of the list
    // (Not sure if we should add at the start or at the end of the list)
    list<Orders>::iterator end = OrdersList.end();
    OrdersList.insert(end, order);
  };

 private:
};