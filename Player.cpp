#include "Player.h"

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

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

// Constructor to create player with arbitrary list of Territory, Card and
// Order pointers.
Player::Player(int nTerritories, int nCards, int nOrders) {
  // Populate list of Territories.
  territories = createTerritoryList(nTerritories);

  // ***********Populate list of Cards randomly.*****************
  int i = 0;
  // Deck* fakeDeck = new Deck(3);
  // cout << "Finished creating deck, now draw cards " << endl;
  // while (i < nCards) {
  //   cout << "Drawing cards, i = " + to_string(i) << endl;
  //   (*cards).drawCard(*fakeDeck);
  //   i++;
  //   cout << "end of while loop, i = " + to_string(i) << endl;
  // }

  cout << "Finished adding cards, soon to create orders" << endl;

  // Populate OrdersList with random Orders
  orders = new OrdersList();
  i = 0;
  while (i < nOrders) {
    (*orders).add(new Order(static_cast<Order::OrderType>(rand() % 6)));
    i++;
  }
}

// //TODO: Decide whether to make deep or shallow copies of lists.
// // Copy Constructor
// Player::Player(const Player& player) {
//   // Making new pointers to all territories in player's territory list.
//   territories = player.territories;

//   // Overloaded = in Hand class creates deep copy
//   *cards = *player.cards;

//   // Overloaded = in OrdersList class creates shallow copy
//   *orders = *player.orders;
// }

// Returns a list of Territories to Attack
list<Node*> Player::toAttack() {
  // Populate list of Territories.
  list<Node*> territoriesToAttack = createTerritoryList(5);

  return territoriesToAttack;
};

// Returns a list of Territories to Defend (All of the player's currently owned
// territories)
list<Node*> Player::toDefend() { return territories; };

void Player::issueOrder() {
  // Create and add random order to List of Orders
  Order* newOrder = new Order(static_cast<Order::OrderType>(rand() % 6));
  (*orders).add(newOrder);
}

//=======================================================

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

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& strm, Player& player) {
  strm << endl << "List of player's territories: " << endl;
  for (std::list<Node*>::iterator it1 = player.territories.begin();
       it1 != player.territories.end(); ++it1) {
    strm << **it1;
  }

  // strm << endl << "List of player's cards: " << endl;
  // strm << *player.cards;

  strm << endl << "List of player's orders: " << endl;
  strm << *player.orders;

  return strm;
}

// Overloaded Assignment Operator
Player& Player::operator=(const Player& player) {
  if (this == &player) return *this;

  // Shallow copy of territory list
  territories = player.territories;

  // Overloaded = in Hand class creates deep copy
  *cards = *player.cards;

  // Overloaded = in OrdersList class creates shallow copy
  *orders = *player.orders;

  return *this;
}