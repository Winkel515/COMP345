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

// Default Constructor
Player::Player() {
  reinforcementPool = 0;
  cards = new Hand();
  orders = new OrdersList();
}

Player::Player(string name) {
  this->name = name;
  reinforcementPool = 0;
  cards = new Hand();
  orders = new OrdersList();
}

// Parameterized constructor for testing purposes
Player::Player(int nTerritories, int nCards, int nOrders) {
  // Populate list of Territories.
  territories = createTerritoryList(nTerritories);

  // Create deck and draw hand
  cards = new Hand();
  Deck* fakeDeck = new Deck(3);
  for (int i = 0; i < nCards; i++) {
    (*cards).drawCard(fakeDeck);
  }

  // Populate OrdersList with random Orders
  orders = new OrdersList();
  for (int i = 0; i < nOrders; i++) {
    (*orders).add(new Order(static_cast<Order::OrderType>(rand() % 6)));
  }
}

// Copy Constructor makes shallow copies of members because we want functions to
// be able to change the pointed to values.
Player::Player(const Player& player) {
  territories = player.territories;
  *cards = Hand(*player.cards);
  *orders = OrdersList(*player.orders);
  name = player.name;
  reinforcementPool = player.reinforcementPool;
}

// Destructor
Player::~Player() {
  // delete all territory pointers in list
  for (std::list<Territory*>::iterator it1 = territories.begin();
       it1 != territories.end(); ++it1) {
    delete *it1;
    *it1 = NULL;
  }

  delete orders;
  delete cards;
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& strm, Player& player) {
  strm << endl << "List of player's territories: " << endl;
  for (std::list<Territory*>::iterator it1 = player.territories.begin();
       it1 != player.territories.end(); ++it1) {
    strm << **it1;
  }

  strm << endl << "List of player's cards: " << endl;
  strm << *player.cards;

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

// Returns a list of Territories to Attack
list<Territory*> Player::toAttack() {
  list<Territory*> territoriesToAttack = createTerritoryList(3);
  return territoriesToAttack;
};

// Returns a list of Territories to Defend (All of the player's currently owned
// territories)
list<Territory*> Player::toDefend() { return territories; };

void Player::issueOrder(Order* newOrder) { (*orders).add(newOrder); }

void Player::addTerritory(Territory* territory) {
  territories.push_back(territory);
}

// For Testing:
void Player::issueOrder() {
  // Create and add random order to List of Orders
  Order* newOrder = new Order(static_cast<Order::OrderType>(rand() % 6));
  (*orders).add(newOrder);
}

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

void Player::addReinforcements(int n) { reinforcementPool += n; }

Hand* Player::getHand() { return cards; }

std::list<Territory*> Player::getTerritories() { return territories; }