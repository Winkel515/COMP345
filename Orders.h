#include <iostream>
#include <list>
#include <string>

using namespace std;

class Orders {
 public:
  string type;
  int units;
  int source;  // will change to node once territories are implemented
  int target;  // same here
  void validate();
  void execute();
  Orders(string type, int units, int source, int target);
};

class OrdersList {
 public:
  OrdersList(list<Orders*> OrdersList);
  void move(list<Orders*> OrdersList, int initial, int final);
  void remove(list<Orders*> OrdersList, Orders order);
  void add(list<Orders*> OrdersLis, Orders order);
};