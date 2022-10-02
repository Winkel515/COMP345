#pragma once

#include <iostream>
#include <list>
using namespace std;

namespace Fake {
class Territory {
 public:
  int value;
};

class Order {
 public:
  int value;
};

class Card {
 public:
  int value;
};
};  // namespace Fake

class Player {
  std::list<Fake::Territory*> territories;
  std::list<Fake::Order*> orders;
  std::list<Fake::Card*> cards;

 public:
  Player(const Player& p);
  std::list<Fake::Territory*> toDefend();
  std::list<Fake::Territory*> toAttack();
  void issueOrder();
  void testListOrder();
  std::list<Fake::Territory*> getTeritories();
  std::list<Fake::Order*> getOrders();
  std::list<Fake::Card*> getCards();
  Player& operator=(const Player& player);
  friend std::ostream& operator<<(std::ostream& strm, Player& pl);
};
