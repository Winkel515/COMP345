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

Player* Player::neutralPlayer = NULL;

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
std::ostream& operator<<(std::ostream& strm, const Player& player) {
  strm << "\nList of player's territories: " << endl;

  for(int i =0; i < player.territories.size(); i++){
    strm << *(player.territories[i]);
  }

  strm << endl << "List of player's cards: " << endl;

  strm << *(player.cards);

  strm << endl << "List of player's orders: " << endl;
  strm << *(player.orders);

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
  for (std::vector<Territory*>::iterator it1 = territories.begin();
       it1 != territories.end(); ++it1) {
    vector<Territory*> neighbours = (*it1)->adj;

    // Check if neighbour territories are attackable.
    for (std::vector<Territory*>::iterator it2 = neighbours.begin();
         it2 != neighbours.end(); ++it2) {
      // // Check if already in toAttack list.
      bool notInToAttack = true;
      for (std::vector<Territory*>::iterator it3 = territoriesToAttack.begin();
           it3 != territoriesToAttack.end(); ++it3) {
        if (*it2 == *it3) {
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
vector<Territory*> Player::toDefend() { return territories; };

void Player::addTerritory(Territory* territory) {
  territories.push_back(territory);
}

// Helper function for issueOrder()
bool playCard(Player* player, Card* card, vector<Card*> hand, Deck* deck) {

  cout << player->getName() << " is adding a special order: " << *card << endl;

  // Return card to Deck
  card->play(deck);
  // remove card from hand after playing
  hand.erase(find(hand.begin(),hand.end(), card), hand.end());
  player->getHand()->setCards(hand);

  return true;
}

// helper function for Deliverable 2. Can be replaced by getTerritoryChoice() or
// a similar method when choices are introduced
Territory* getRandomTerritory(vector<Territory*> territories) {
  std::random_device seed;
  std::mt19937 gen{seed()};  // seed the generator
  std::uniform_int_distribution<> dist{
      0, static_cast<int>(territories.size()) - 1};  // set min and max
  int index = dist(gen);                             // generate number
  return territories.at(index);
}

// Returns true if player issues an order, false if they are done issuing orders
bool Player::issueOrder() {
  // Deploy all Reinforcements
  if (reinforcementPool > 0 && issueOrdersCount == 0) {
    // Hardcoded to deploy in rounds of 10 to random territory
    int numOfArmies = 10;
    if (numOfArmies > reinforcementPool) {
      numOfArmies = reinforcementPool;
    }
    Territory* target = getRandomTerritory(toDefend());
    orders->add(new Deploy(target, this, numOfArmies));
    reinforcementPool -= numOfArmies;
    cout << (*this).name << " added a Deploy Order: " << numOfArmies << " armies to "
         << target->getName() << " territory \n";
    return true;
  }

  else if (issueOrdersCount == 0) {
    // Demonstrate Advance using toDefend()
    Territory* target = getRandomTerritory(toDefend());
    Territory* source = NULL;
    vector<Territory*> adjacent = target->adj;
    // Find an adjacent territory that is owned by the calling player.
    for (vector<Territory*>::iterator it = adjacent.begin();
         it != adjacent.end(); ++it) {
      if ((*it)->owner == this) {
        source = *it;
      }
    }
    if (source != NULL) {
      // Move 2 armies from source to target
      orders->add(new Advance(target, source, this, 2));
      cout << (*this).name << " added an Advance Order:  2 armies from " << source->getName()
           << " to " << target->getName() << "\n";
    }
    issueOrdersCount++;
    return true;
  }

  else if (issueOrdersCount == 1) {
    // Demonstrate Advance using toAttack()
    Territory* target = getRandomTerritory(toAttack());
    Territory* source = NULL;
    vector<Territory*> adjacent = target->adj;
    // Find an adjacent territory that is owned by the calling player.
    for (auto it = adjacent.begin(); it != adjacent.end(); ++it) {
      if ((*it)->owner == this) {
        source = *it;
      }
    }
    // Move 2 armies from source to target
    if (source != NULL) {
      orders->add(new Advance(target, source, this, 2));
      cout << (*this).name << " added an Advance Order: 2 armies from " << source->getName()
           << " to " << target->getName() << "\n";
    }
    issueOrdersCount++;
    return true;
  }

  // Playing Card Functionality
  // Hardcoded at 4 to demonstrate multiple cards
  else if (issueOrdersCount < 4 && cards->getCards().size() != 0) {
    // Cards functionality
    vector<Card*> hand = cards->getCards();
    Card* cardToPlay = hand.back();
    Deck* deck = cards->getDeck();

    cout << endl << getName() << " is choosing a card to play: " << *cardToPlay << endl;

    switch(cardToPlay->GetType()) {
      // Bomb
      case 0: {
        Territory* target = getRandomTerritory(toAttack());
        orders->add(new Bomb(target, this));
        cout << "Bombing " << *target << endl;
        break;
      }
      // Reinforcement
      case 1: {
        // TODO JOHN: Now that reinforcementPool > 0, do we have to deploy?
        reinforcementPool += 5;
        break;
      }
      // Blockade
      case 2: {
        Territory* target = getRandomTerritory(toDefend());
        orders->add(new Blockade(target, this, neutralPlayer));
        cout << "Blockading " << *target << endl;
        break;
      }
      // Airlift
      case 3: {
        int numArmiesToMove = 2;
        Territory* target = getRandomTerritory(toDefend());
        Territory* source = getRandomTerritory(toDefend());
        // Ensure source and target are different
        //TODO JOHN: Account for if player only has 1 territory
        while (source == target) {
          source = getRandomTerritory(toDefend());
        }
        orders->add(new Airlift(target, source, this, numArmiesToMove));
        cout << "Airlifting from " << *target << " to " << *source << endl;
        break;
      }
      // Diplomacy
      case 4: {
        Territory* target = getRandomTerritory(toAttack());
        orders->add(new Negotiate(target, this));
        cout << "Negotiating with " << *target << endl;
      }
      //end of switch
    }

    return playCard(this, cardToPlay, hand, deck);
    // End of while loop to play cards
  }

  // LogObserver *orderView = new LogObserver(newOrder);

  // No order Issued
  issueOrdersCount = 0;
  return false;
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

string Player::getName() { return name; }

void Player::setHand(Hand* hand){cards = hand;}