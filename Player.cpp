#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>


#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include "Player.h"

// Default Constructor
Player::Player() {
  reinforcementPool = 0;
  ConqueredTerritoryFlag = false;
  cards = new Hand();
  orders = new OrdersList();
  //LogObserver* OrdersListView = new LogObserver(orders);
}

Player::Player(string name) {
  this->name = name;
  reinforcementPool = 0;
  cards = new Hand();
  orders = new OrdersList();
  ConqueredTerritoryFlag = false;
  //LogObserver* OrdersListView = new LogObserver(orders);
}


// Parameterized constructor for testing purposes
Player::Player(int nTerritories, int nCards, int nOrders) {
  // Populate list of Territories.
  territories = createTerritoryList(nTerritories);
  ConqueredTerritoryFlag = false;

  // Create deck and draw hand
  cards = new Hand();
  Deck* fakeDeck = new Deck(3);
  cards->setDeck(fakeDeck);
  for (int i = 0; i < nCards; i++) {
    (*cards).drawCard();
  }

  // Populate OrdersList with random Orders
  orders = new OrdersList();
  for (int i = 0; i < nOrders; i++) {
    //(*orders).add(new Order(static_cast<Order::OrderType>(rand() % 6)));
  }
  //LogObserver* OrdersListView = new LogObserver(orders);
}


// Copy Constructor makes shallow copies of members because we want functions to
// be able to change the pointed to values.
Player::Player(const Player& player) {
  territories = player.territories;
  *cards = Hand(*player.cards);
  *orders = OrdersList(*player.orders);
  name = player.name;
  reinforcementPool = player.reinforcementPool;
  ConqueredTerritoryFlag = false;
}

// Destructor
Player::~Player() {
  delete orders;
  delete cards;
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& strm, Player& player) {
  strm << endl << "List of player's territories: " << endl;
  for (std::vector<Territory*>::iterator it1 = player.territories.begin();
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
std::vector<Territory*> Player::toAttack() {
  std::vector<Territory*> territoriesToAttack = createTerritoryList(3);
  return territoriesToAttack;
};

// Returns a list of Territories to Defend (All of the player's currently owned
// territories)
std::vector<Territory*> Player::toDefend() { return territories; };

void Player::issueOrder(Order* newOrder) { (*orders).add(newOrder); }

void Player::addTerritory(Territory* territory) {
  territories.push_back(territory);
}

/*
void Player::issueOrder() {
  // Create and add random order to List of Orders
  Order* newOrder = new Order(static_cast<Order::OrderType>(rand() % 6));
  (*orders).add(newOrder);
  //LogObserver *orderView = new LogObserver(newOrder);
}
*/

// Helper method to create territory list
std::vector<Territory*> Player::createTerritoryList(int nTerritories) {
  std::vector<Territory*> territories;

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

std::vector<Territory*> Player::getTerritories() { return territories; }

bool Player::getConcqueredFlag(){ return ConqueredTerritoryFlag; }

void Player::setConcqueredFlag(bool flag){ ConqueredTerritoryFlag = flag; }

vector<Player*> Player::getDiplomaticAllies(){return diplomaticAllies;}

void Player::addDiplomaticAlly(Player* ally) { diplomaticAllies.push_back(ally);}

void Player::clearDiplomaticAllies(){ diplomaticAllies.clear();}

OrdersList* Player::getOrderList() {
  return orders;
}