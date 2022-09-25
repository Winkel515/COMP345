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
  list<Orders*> OrdersList;

  void move(list<Orders*> OrdersList, int initial, int final) {
    // Declare 2 iterators at the begining of the list
    list<Orders*>::iterator itInitial = OrdersList.begin();
    list<Orders*>::iterator itFinal = OrdersList.begin();

    // Move the iterators to the inital and final positions
    advance(itInitial, initial);
    advance(itFinal, final);

    // Move the elements with splice function
    OrdersList.splice(itFinal, OrdersList, itInitial);
  };

  void remove(list<Orders*> OrdersList, int index) {
    list<Orders*>::iterator it = OrdersList.begin();

    // Move interator to position
    advance(it, index);

    OrdersList.erase(it);
  };

  void add(list<Orders*> OrdersList, Orders order) {
    // Not sure if we should add to the begining or the end
    OrdersList.emplace_back(order);
  };

 private:
};