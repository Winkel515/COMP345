#pragma once

#include <iostream>
#include <list>

#include "Cards.h"
#include "Map.h"
using namespace std;

class Player {
  std::list<Node*> territories;
  // std::list<Order*> orders;
  std::list<Card*> cards;

 public:
  Player(int nTerritories);
  Player(const Player& p);
  std::list<Node*> toDefend();
  std::list<Node*> toAttack();
  void issueOrder();
  void testListOrder();
  Player& operator=(const Player& player);
  friend std::ostream& operator<<(std::ostream& strm, Player& pl);
};
