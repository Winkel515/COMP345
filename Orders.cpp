#include "Orders.h"

#include <sstream>

using namespace std;

// default constructor
Order::Order() {}
// Order constructor
Order::Order(Order::OrderType type) {
  cout << type << " Order created with default constructor" << endl;
  TypeOfOrder = type;
}

// Order copy constructor
Order::Order(const Order &order) : TypeOfOrder(order.TypeOfOrder) {
  cout << order.TypeOfOrder << " Order created with copy constructor" << endl;
}

// Order assignment operator
Order &Order::operator=(const Order &order) {
  TypeOfOrder = order.TypeOfOrder;
  return *this;
}

// Order destructor
Order::~Order() { cout << "Destroyed Order" << endl; }

// Order insertion stream operator
ostream &operator<<(ostream &out, const Order &o) {
  int type = o.GetType();
  std::string types[] = {"Deploy",   "Advance", "Bomb",
                         "Blockade", "Airlift", "Negotiate"};
  out << types[type] << endl;
  return out;
}

// Validate function
void Order::validate() {
  // Will need to check player territories to see if order is valid
  cout << "Order " << this->GetType() << " validated" << endl;
};

// Execute function
void Order::execute() {
  validate();
  cout << "Order " << this->GetType() << " did this" << endl;
};

// Accessor methods
Order::OrderType Order::GetType() const { return TypeOfOrder; }

// Mutator methods
void Order::SetType(Order::OrderType type) { TypeOfOrder = type; }

// Default OrderList constructor
OrdersList::OrdersList() {
  vector<Order *> o;
  this->ListOfOrders = o;
}

// Orderlist copy constructor
OrdersList::OrdersList(const OrdersList &oL) { ListOfOrders = oL.ListOfOrders; }

// Assignment operator
OrdersList &OrdersList::operator=(const OrdersList &oL) {
  if (&oL != this) {
    this->ListOfOrders = oL.ListOfOrders;
  }
  return *this;
}

void OrdersList::move(int initial, int final) {
  // Intial index must be lower than size
  if (initial >= ListOfOrders.size() || initial < 0) return;

  // If final index is out of bounds, use list size as index
  int newIndex = min(max(final, 0), (int)ListOfOrders.size());

  Order *movedOrder = ListOfOrders[initial];
  ListOfOrders.erase(ListOfOrders.begin() + initial);
  ListOfOrders.insert(ListOfOrders.begin() + newIndex, movedOrder);
};

void OrdersList::remove(int index) {
  // Index must be lower than size
  if (index >= ListOfOrders.size() || index < 0) return;

  // Delete the pointer
  delete ListOfOrders[index];
  ListOfOrders.erase(ListOfOrders.begin() + index);
};

void OrdersList::add(Order *order) {
  // Not sure if we should add to the begining or the end
  ListOfOrders.push_back(order);
};

// OrderList destructor
OrdersList::~OrdersList() {
  // Remove all the pointers in the vector
  for (int i = 0; i < this->ListOfOrders.size(); i++) {
    delete this->ListOfOrders[i];
    this->ListOfOrders[i] = nullptr;
  }
  this->ListOfOrders.clear();
}

// Stream insertion operator
ostream &operator<<(ostream &o, const OrdersList &ol) {
  stringstream ss;

  ss << "Order list:" << endl;

  for (Order *order : ol.ListOfOrders) {
    ss << "\t"
       << "Order " << order->GetType() << " is present in the list,\n";
  }

  return o << ss.str() << endl;
}

// execute all orders in the list
void OrdersList::executeOrders() {
  for (Order *order : ListOfOrders) {
    order->execute();
  }
};