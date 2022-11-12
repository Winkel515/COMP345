#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>


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

//TODO JOHN: Make this more efficient.
// Returns a list of Territories to Attack
list<Territory*> Player::toAttack() {
  list<Territory*> territoriesToAttack;

  //Find all neighbouring territories
  for (auto it1 = territories.begin(); it1 != territories.end(); ++it1) {
    vector<Territory*> neighbours = (*it1)->adj;

    //Check if adjacent territories are attackable.
    for(auto it2 = neighbours.begin(); it2 != neighbours.end(); ++it2){

      //Check if it's in our territory list. 
      bool notInOurTerritories = true;
      for(auto it3 = territories.begin(); it3 != territories.end(); ++it3){
        if (*it2 = *it3){
          notInOurTerritories = false;
        }
      }

      //Check if already in toAttack list. 
      bool notInToAttack = true;
      for(auto it3 = territoriesToAttack.begin(); it3 != territoriesToAttack.end(); ++it3){
        if (*it2 = *it3){
          notInToAttack = false;
        }
      }

      if(notInOurTerritories && notInToAttack){
        territoriesToAttack.push_back(*it2);
      }
    }
  }
  return territoriesToAttack;
};

// Returns a list of Territories to Defend (All of the player's currently owned
// territories)
list<Territory*> Player::toDefend() { 
  //TODO JOHN: Implement logic here
  return territories; 
};

//TODO JOHN: Delete if obsolete
void Player::issueOrder(Order* newOrder) { (*orders).add(newOrder); }

void Player::addTerritory(Territory* territory) {
  territories.push_back(territory);
}

//Returns true if player issues an order, false if they are done issuing orders
bool Player::issueOrder() {

  //Deploy Reinforcements
  if(reinforcementPool > 0){
    // orders->add(new Deploy()); //TODO JOHN:  Make sure deploy is concrete


  }
  

  // TODO JOHN: Hardcode issueOrder() implementation.

  //TODO JOHN: Deploy orders only if reinforcements > 0


  return true;



  // // Create and add random order to List of Orders
  // Order* newOrder = new Order(static_cast<Order::OrderType>(rand() % 6));
  // (*orders).add(newOrder);
  //LogObserver *orderView = new LogObserver(newOrder);
}


// Helper method to create territory list
list<Territory*> Player::createTerritoryList(int nTerritories) {
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

bool Player::getConcqueredFlag(){ return ConqueredTerritoryFlag; }

void Player::setConcqueredFlag(bool flag){ ConqueredTerritoryFlag = flag; }

vector<Player*> Player::getDiplomaticAllies(){return diplomaticAllies;}

void Player::addDiplomaticAlly(Player* ally) { diplomaticAllies.push_back(ally);}

void Player::clearDiplomaticAllies(){ diplomaticAllies.clear();}

OrdersList* Player::getOrderList() {
  return orders;
}