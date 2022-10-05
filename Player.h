#pragma once

#include <iostream>
#include <list>

class Card;
class Node;
class Order;
using namespace std;

class Player {
  std::list<Node*> territories;
  std::list<Order*> orders;
  std::list<Card*> cards;

 public:
  Player(int nTerritories, int nCards, int nOrders);
  Player(const Player& p);
  std::list<Node*> toDefend();
  std::list<Node*> toAttack();
  void issueOrder();
  void testListOrder();
  Player& operator=(const Player& player);
  friend std::ostream& operator<<(std::ostream& strm, Player& pl);
};

list<Node*> createTerritoryList(int nTerritories);