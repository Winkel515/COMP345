#pragma once

#include <iostream>
#include <list>

class Card;
class Territory;
class OrdersList;
class Hand;
class Order;
using namespace std;

class Player {
  std::list<Territory*> territories;
  OrdersList* orders;
  Hand* cards;
  bool ConqueredTerritoryFlag;

 public:
  Player();
  Player(int nTerritories, int nCards, int nOrders);
  Player(const Player& player);
  ~Player();
  std::list<Territory*> toDefend();
  std::list<Territory*> toAttack();
  void issueOrder(Order* newOrder);
  void issueOrder();  // For Testing
  void testListOrder();
  Player& operator=(const Player& player);
  friend std::ostream& operator<<(std::ostream& strm, Player& pl);
};

list<Territory*> createTerritoryList(int nTerritories);
