#pragma once

#include <iostream>
#include <list>

class Card;
class Node;
class OrdersList;
class Hand;
class Order;
using namespace std;

class Player {
  std::list<Node*> territories;
  OrdersList* orders;
  Hand* cards;

 public:
  Player();
  Player(int nTerritories, int nCards, int nOrders);
  Player(const Player& player);
  ~Player();
  std::list<Node*> toDefend();
  std::list<Node*> toAttack();
  void issueOrder(Order* newOrder);
  void issueOrder();  // For Testing
  void testListOrder();
  Player& operator=(const Player& player);
  friend std::ostream& operator<<(std::ostream& strm, Player& pl);
};

list<Node*> createTerritoryList(int nTerritories);
