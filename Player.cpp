#include "Player.h"

#include <cstdlib>
#include <iostream>
#include <list>

using namespace std;

// Overload stream insertion operator
std::ostream& operator<<(std::ostream& strm, Player& p) {
  strm << "This is the overloaded stream insertion operator" << endl;

  return strm;
}

namespace PlayerUtils {

// Populate a list of arbitrary territories
list<Fake::Territory*> getArbitraryTerritories(int size) {
  list<Fake::Territory*> territories;

  int counter = 0;
  while (counter <= size) {
    Fake::Territory* territory = new Fake::Territory;
    territory->value = rand() % 100;

    counter++;

    territories.push_back(territory);
  }
  return territories;
}

// Outputs a list of Fake Territories
void printTerritories(list<Fake::Territory*> territories) {
  for (list<Fake::Territory*>::iterator i = territories.begin();
       i != territories.end(); i++) {
    cout << "Territory " << ((Fake::Territory*)*i)->value << " ";
  }

  cout << "\n";
}
}  // namespace PlayerUtils

// Returns a list of Territories to Defend
list<Fake::Territory*> Player::toDefend() {
  list<Fake::Territory*> territories = PlayerUtils::getArbitraryTerritories(3);
  cout << "Defending ";
  PlayerUtils::printTerritories(territories);
  return territories;
};

// Returns a list of Territories to Attack
list<Fake::Territory*> Player::toAttack() {
  list<Fake::Territory*> territories = PlayerUtils::getArbitraryTerritories(4);
  cout << "Attacking ";
  PlayerUtils::printTerritories(territories);
  return territories;
};

// Creates a new order in the Order List
void Player::issueOrder() {
  Fake::Order* order = new Fake::Order;
  order->value = rand() % 100;

  this->orders.push_back(order);
};

// Lists all the orders in Order List
void Player::testListOrder() {
  list<Fake::Order*> orders = this->orders;
  cout << "List orders: ";
  for (list<Fake::Order*>::iterator i = orders.begin(); i != orders.end();
       i++) {
    cout << "Order " << ((Fake::Order*)*i)->value << " ";
  }
  cout << "\n";
}