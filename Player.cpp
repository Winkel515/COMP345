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

// TODO: Delete Main, transfer to main.cpp
//  // Test main for Player Functionality
//  int main() {
//    testPlayers();

//   return 0;
// }

// Default Constructor
Player::Player() {}

// Constructor for testing purposes
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

// Copy Constructor makes shallow copies of members because we want functions to
// be able to change the pointed to values.
Player::Player(const Player& player) {
  territories = player.territories;
  *cards = Hand(*player.cards);
  *orders = OrdersList(*player.orders);
}

// Destructor
Player::~Player() {
  delete orders;
  // Iterate through and call method to put back cards. In Hand class.: void
  // swapCardToDeck(Deck& deck, int indexOfCard);
  delete cards;
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& strm, Player& player) {
  strm << endl << "List of player's territories: " << endl;
  for (std::list<Territory*>::iterator it1 = player.territories.begin();
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

  territories = player.territories;  // Shallow copy
  *cards = *player.cards;            // shallow copy
  *orders = *player.orders;          // Shallow copy

  return *this;
}

// ====================================================

// Returns a list of Territories to Attack
list<Territory*> Player::toAttack() {
  list<Territory*> territoriesToAttack = createTerritoryList(5);
  return territoriesToAttack;
};

// Returns a list of Territories to Defend (All of the player's currently owned
// territories)
list<Territory*> Player::toDefend() { return territories; };

void Player::issueOrder(Order* newOrder) { (*orders).add(newOrder); }

// For Testing:
void Player::issueOrder() {
  // Create and add random order to List of Orders
  Order* newOrder = new Order(static_cast<Order::OrderType>(rand() % 6));
  (*orders).add(newOrder);
}

//=======================================================

// Helper method to create territory list
list<Territory*> createTerritoryList(int nTerritories) {
  list<Territory*> territories;

  int i = 0;
  while (i < nTerritories) {
    territories.push_back(
        new Territory("Territory " + to_string(i + 1), "Some Continent"));
    i++;
  }

  return territories;
}
