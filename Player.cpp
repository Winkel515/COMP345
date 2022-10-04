#include "Player.h"

#include <cstdlib>
#include <iostream>
#include <list>

#include "Cards.h"
#include "Map.h"

using namespace std;

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& strm, Player& p) {
  strm << "This is the overloaded stream insertion operator" << endl;

  return strm;
}

// Default constructor creating arbitrary list of Terriotires
Player::Player(int nTerritories) {
  // Populate list of Territories randomly.
  int i = 0;
  while (i < nTerritories) {
    territories.push_back(new Node("Territory" + i, "Some Continent"));
    i++;
  }
}

int main() {
  Player* p1 = new Player(3);
  cout << *p1 << endl;

  cout << "Hello from main";
  return 0;
}

// Copy Constructor

// Player(const Player& player) {
//   int tsize = player.getTerritories.size();
//   for (int i = 0; i < tsize; i++) {
//     territories.push_back(new Territory(player.territories[i]));
//   }

//   int osize = player.getOrders.size();
//   for (int i = 0; i < osize; i++) {
//     orders.push_back(new Order(player.orders[i]));
//   }

//   int csize = player.getCards().size();
//   for (int i = 0; i < csize; i++) {
//     cards.push_back(new Card(player.cards[i]));
//   }
// }

// Overloaded Assignment Operator

// Player& Player::operator=(const Player& player) {
//   if (this == &player) return *this;

//   tsize = player.getTerritories.size();
//   for (int i = 0; i < tsize; i++) {
//     territories.push_back(new Territory(player.territories[i]));
//   }

//   osize = player.getOrders.size();
//   for (int i = 0; i < osize; i++) {
//     orders.push_back(new Order(player.orders[i]));
//   }

//   csize = player.getCards().size();
//   for (int i = 0; i < csize; i++) {
//     cards.push_back(new Card(player.cards[i]));
//   }

//   return *this;
// }

// namespace PlayerUtils {

// // Populate a list of arbitrary territories
// list<Fake::Territory*> getArbitraryTerritories(int size) {
//   list<Fake::Territory*> territories;

//   int counter = 0;
//   while (counter <= size) {
//     Fake::Territory* territory = new Fake::Territory;
//     territory->value = rand() % 100;

//     counter++;

//     territories.push_back(territory);
//   }
//   return territories;
// }

// // Outputs a list of Fake Territories
// void printTerritories(list<Fake::Territory*> territories) {
//   for (list<Fake::Territory*>::iterator i = territories.begin();
//        i != territories.end(); i++) {
//     cout << "Territory " << ((Fake::Territory*)*i)->value << " ";
//   }

//   cout << "\n";
// }
// }  // namespace PlayerUtils

// // Returns a list of Territories to Defend
// list<Fake::Territory*> Player::toDefend() {
//   list<Fake::Territory*> territories =
//   PlayerUtils::getArbitraryTerritories(3); cout << "Defending ";
//   PlayerUtils::printTerritories(territories);
//   return territories;
// };

// // Returns a list of Territories to Attack
// list<Fake::Territory*> Player::toAttack() {
//   list<Fake::Territory*> territories =
//   PlayerUtils::getArbitraryTerritories(4); cout << "Attacking ";
//   PlayerUtils::printTerritories(territories);
//   return territories;
// };

// // Creates a new order in the Order List
// void Player::issueOrder() {
//   Fake::Order* order = new Fake::Order;
//   order->value = rand() % 100;

//   this->orders.push_back(order);
// };

// // Lists all the orders in Order List
// void Player::testListOrder() {
//   list<Fake::Order*> orders = this->orders;
//   cout << "List orders: ";
//   for (list<Fake::Order*>::iterator i = orders.begin(); i != orders.end();
//        i++) {
//     cout << "Order " << ((Fake::Order*)*i)->value << " ";
//   }
//   cout << "\n";
// }