#include "Orders.h"

class Orders {
 private:
  string type;
  int units;
  int source;  // will change to node once territories are implemented
  int target;  // same here
  string orderEffect;
  enum validTypes { deploy, advance, bomb, blockade, airlift, negotiate };

 public:
  // Order constructor
  Orders::Orders(string oType, int oUnits, int oSource, int oTarget) {
    setOrder(oType, oUnits, oSource, oTarget);
  };

  friend ostream &operator<<(ostream &output, const Orders &o) {
    // Will need to change for different kinds of orders
    output << "Order " + o.type + " from " + to_string(o.source) + " to " +
                  to_string(o.target) +
                  " number of units: " + to_string(o.units);
    return output;
  }

  // Order member function
  void Orders::setOrder(string oType, int oUnits, int oSource, int oTarget) {
    type = oType;
    units = oUnits;
    source = oSource;
    target = oTarget;
  };

  void Orders::validate(){
      // Will need territories to check if order is valid
  };

  void Orders::execute() {
    orderEffect = "Order successful/unsuccessful";

    cout << orderEffect << endl;
  };
};

class OrdersList {
 private:
  list<Orders *> OrdersList;

 public:
  void OrdersList::move(int initial, int final) {
    // Declare 2 iterators at the begining of the list
    list<Orders *>::iterator itInitial = OrdersList.begin();
    list<Orders *>::iterator itFinal = OrdersList.begin();

    // Move the iterators to the inital and final positions
    advance(itInitial, initial);
    advance(itFinal, final);

    // Move the elements with splice function
    OrdersList.splice(itFinal, OrdersList, itInitial);
  };

  void OrdersList::remove(int index) {
    list<Orders *>::iterator it = OrdersList.begin();

    // Move interator to position
    advance(it, index);

    OrdersList.erase(it);
  };

  void OrdersList::add(Orders order) {
    // Not sure if we should add to the begining or the end
    OrdersList.emplace_back(order);
  };
};