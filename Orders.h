#include <iostream>
#include <list>
#include <string>

using namespace std;

class Orders {
 private:
  string type;
  int units;
  int source;  // will change to node once territories are implemented
  int target;  // same here
  string orderEffect;
  enum validTypes {};

 public:
  Orders(string oType, int oUnits, int oSource, int oTarget);
  friend ostream &operator<<(ostream &output, const Orders &o);
  void setsetOrder(string oType, int oUnits, int oSource, int oTarget);
  void describeOrder();
  void validate();
  void execute();
};

class OrdersList {
 private:
  list<Orders *> OrdersList;

 public:
  void move(int initial, int final);
  void remove(Orders order);
  void add(Orders order);
};