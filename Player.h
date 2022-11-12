#pragma once

#include <iostream>
#include <list>
#include <string>
#include "Cards.h"
#include "Map.h"
#include "Orders.h"



class Player {
  private:
    std::list<Territory*> territories;
    OrdersList* orders;
    Hand* cards;
    bool ConqueredTerritoryFlag;
    string name;
    int reinforcementPool;
    std::vector<Player*> diplomaticAllies;

 public:
  Player();
  Player(int nTerritories, int nCards, int nOrders);
  Player(string name);
  Player(const Player& player);
  ~Player();
  std::list<Territory*> toDefend();
  std::list<Territory*> toAttack();
  void issueOrder(Order* newOrder);
  void issueOrder();  // For Testing
  void testListOrder();
  Player& operator=(const Player& player);
  friend std::ostream& operator<<(std::ostream& strm, Player& pl);
  void addTerritory(Territory*);
  void addReinforcements(int);
  Hand* getHand();
  std::list<Territory*> getTerritories();
  OrdersList* Player::getOrderList();
  bool getConcqueredFlag();
  void setConcqueredFlag(bool flag);
  std::vector<Player*> getDiplomaticAllies();
  void addDiplomaticAlly(Player* ally);
  void clearDiplomaticAllies();
  list<Territory*> createTerritoryList(int nTerritories);

};
