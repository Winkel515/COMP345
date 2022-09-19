#include <list>
#pragma once

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
  std::list<Fake::Territory*> toDefend();
  std::list<Fake::Territory*> toAttack();
  void issueOrder();
  void testListOrder();
};