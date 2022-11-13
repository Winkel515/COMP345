#include "Player.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <random>
#include <vector>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"

// Default Constructor
Player::Player() {
  issueOrdersCount = 0;
  reinforcementPool = 0;
  ConqueredTerritoryFlag = false;
  cards = new Hand();
  orders = new OrdersList();
}

Player::Player(string name) {
  issueOrdersCount = 0;
  this->name = name;
  reinforcementPool = 0;
  cards = new Hand();
  orders = new OrdersList();
  ConqueredTerritoryFlag = false;
  // LogObserver* OrdersListView = new LogObserver(orders);
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
vector<Territory*> Player::toAttack() {
  vector<Territory*> territoriesToAttack;
  // Find all neighbouring territories
  for (auto it1 = territories.begin(); it1 != territories.end(); ++it1) {
    vector<Territory*> neighbours = (*it1)->adj;

    // Check if neighbour territories are attackable.
    for (auto it2 = neighbours.begin(); it2 != neighbours.end(); ++it2) {
      // Check if already in toAttack list.
      bool notInToAttack = true;
      for (auto it3 = territoriesToAttack.begin();
           it3 != territoriesToAttack.end(); ++it3) {
        if (*it2 = *it3) {
          notInToAttack = false;
        }
      }

      // Add territory if it's not already in our list and we aren't the owner
      if (notInToAttack && (**it2).getOwner() != this) {
        territoriesToAttack.push_back(*it2);
      }
    }
  }
  return territoriesToAttack;
};

// Returns a list of Territories to Defend (All of the player's currently owned
// territories)
vector<Territory*> Player::toDefend() {
  // TODO JOHN: Implement logic here
  return territories;
};

// TODO JOHN: Delete if obsolete
void Player::issueOrder(Order* newOrder) { (*orders).add(newOrder); }

void Player::addTerritory(Territory* territory) {
  territories.push_back(territory);
}

// Helper function for issueOrder()
bool playCard(Card* card, vector<Card*> hand, Deck* deck) {
  // Return card to Deck
  card->play(deck);
  // delete pointer and remove from vector
  delete card;
  hand.pop_back();

  return true;
}

// helper function for Deliverable 2. Can be replaced by getTerritoryChoice() or
// a similar method when choices are introduced
Territory* getRandomTerritory(vector<Territory*> territories) {
  std::random_device seed;
  std::mt19937 gen{seed()};  // seed the generator
  std::uniform_int_distribution dist{
      0, static_cast<int>(territories.size()) - 1};  // set min and max
  int index = dist(gen);                             // generate number
  return territories.at(index);
}

// TODO JOHN: Implement a counter to ensure we demonstrate all the possibilities
// TODO JOHN: cout so we see the orders do as they are supposed to.
// Returns true if player issues an order, false if they are done issuing orders
bool Player::issueOrder() {
  // Deploy all Reinforcements
  if (reinforcementPool > 0) {
    // Hardcoded to deploy in rounds of 10 to random territory
    int numOfArmies = 10;
    if (numOfArmies > reinforcementPool) {
      numOfArmies = reinforcementPool;
    }
    Territory* target = getRandomTerritory(toDefend());
    orders->add(new Deploy(target, this, numOfArmies));
    reinforcementPool -= numOfArmies;
    return true;
  }

  else if (issueOrdersCount == 0) {
    // Demonstrate Advance using toDefend()
    Territory* target = getRandomTerritory(toDefend());
    Territory* source;
    vector<Territory*> adjacent = target->adj;
    // Find an adjacent territory that is owned by the calling player.
    for (auto it = adjacent.begin(); it != adjacent.end(); ++it) {
      if ((*it)->owner == this) {
        source = *it;
      }
    }
    // Move 2 armies from source to target
    orders->add(new Advance(target, source, this, 2));
    issueOrdersCount++;
    return true;
  }

  else if (issueOrdersCount == 1) {
    // Demonstrate Advance using toAttack()
    Territory* target = getRandomTerritory(toAttack());
    Territory* source;
    vector<Territory*> adjacent = target->adj;
    // Find an adjacent territory that is owned by the calling player.
    for (auto it = adjacent.begin(); it != adjacent.end(); ++it) {
      if ((*it)->owner == this) {
        source = *it;
      }
    }
    // Move 2 armies from source to target
    orders->add(new Advance(target, source, this, 2));
    issueOrdersCount++;
    return true;
  }

  else if (issueOrdersCount <
           6) {  // Hardcoded at 6 to demonstrate multiple cards

    // TODO JOHN: Demonstrate cards functionality
    vector<Card*> hand = cards->getCards();
    Card* cardToPlay = hand.back();
    Deck* deck = cards->getDeck();

    // Compare Card::CardType() to it's enum values.
    if (cardToPlay->GetType() == 1) {
      Territory* target = getRandomTerritory(toAttack());
      orders->add(new Bomb(target, this));
      issueOrdersCount++;
      return playCard(cardToPlay, hand, deck);
    } else if (cardToPlay->GetType() == 2) {
      // TODO JOHN: Now that reinforcementPool > 0, do we have to deploy?
      reinforcementPool += 5;
      return true;
    } else if (cardToPlay->GetType() == 3) {
      // TODO: Implement blockade once neutral parameter is removed.
      Territory* target = getRandomTerritory(toDefend());
      // Constructor: Blockade(Territory* target, Player* owner, Player*
      // neutral);

      return playCard(cardToPlay, hand, deck);
    } else if (cardToPlay->GetType() == 4) {
      int numArmiesToMove = 2;
      Territory* target = getRandomTerritory(toDefend());
      Territory* source = getRandomTerritory(toDefend());
      // Ensure source and target are different
      while (source == target) {
        source = getRandomTerritory(toDefend());
      }
      orders->add(new Airlift(target, source, this, numArmiesToMove));
      issueOrdersCount++;
      return playCard(cardToPlay, hand, deck);
    } else if (cardToPlay->GetType() == 5) {
      Territory* target = getRandomTerritory(toAttack());
      orders->add(new Negotiate(target, this));
      issueOrdersCount++;
      return playCard(cardToPlay, hand, deck);
    }
  } else {
    // No Order Issued.
    return false;
  }
  // LogObserver *orderView = new LogObserver(newOrder);
}

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

bool Player::getConcqueredFlag() { return ConqueredTerritoryFlag; }

void Player::setConcqueredFlag(bool flag) { ConqueredTerritoryFlag = flag; }

vector<Player*> Player::getDiplomaticAllies() { return diplomaticAllies; }

void Player::addDiplomaticAlly(Player* ally) {
  diplomaticAllies.push_back(ally);
}

void Player::clearDiplomaticAllies() { diplomaticAllies.clear(); }

OrdersList* Player::getOrderList() { return orders; }