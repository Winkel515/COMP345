#include "Player.h"

#include <cstdlib>
#include <iostream>
#include <list>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "PlayerDriver.h"

using namespace std;

// // Test main for Player Functionality
// int main() {
//   testPlayers();

//   return 0;
// }

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& strm, Player& player) {
  strm << endl << "List of player's territories: " << endl;
  for (std::list<Node*>::iterator it1 = player.territories.begin();
       it1 != player.territories.end(); ++it1) {
    strm << **it1;
  }

  strm << endl << "List of player's cards: " << endl;
  for (std::list<Card*>::iterator it2 = player.cards.begin();
       it2 != player.cards.end(); ++it2) {
    strm << **it2;
  }

  strm << endl << "List of player's orders: " << endl;
  for (std::list<Order*>::iterator it3 = player.orders.begin();
       it3 != player.orders.end(); ++it3) {
    strm << **it3;
  }

  return strm;
}

// Constructor to create player with arbitrary list of Territory, Card and
// Order pointers.
Player::Player(int nTerritories, int nCards, int nOrders) {
  // Populate list of Territories.
  territories = createTerritoryList(nTerritories);

  // Populate list of Cards randomly.
  int i = 0;
  while (i < nCards) {
    cards.push_back(new Card(static_cast<Card::CardType>(rand() % 5)));
    i++;
  }

  // Populate list of Orders randomly.
  i = 0;
  while (i < nOrders) {
    orders.push_back(new Order(static_cast<Order::OrderType>(rand() % 6)));
    i++;
  }
}

// Returns a list of Territories to Attack
list<Node*> Player::toAttack() {
  // Populate list of Territories.
  list<Node*> territoriesToAttack = createTerritoryList(5);

  return territoriesToAttack;
};

// Returns a list of Territories to Defend (All of the player's currently owned
// territories)
list<Node*> Player::toDefend() { return territories; };

// Helper method to create territory list
list<Node*> createTerritoryList(int nTerritories) {
  list<Node*> territories;

  int i = 0;
  while (i < nTerritories) {
    territories.push_back(
        new Node("Territory " + to_string(i + 1), "Some Continent"));
    i++;
  }

  return territories;
}

//=========================================================

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