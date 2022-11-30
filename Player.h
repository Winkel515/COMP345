#pragma once

#include <iostream>
#include <list>
#include <string>
#include "Cards.h"
#include "Map.h"
#include "Orders.h"



class Player {
  private:
    OrdersList* orders;
    Hand* cards;
    bool ConqueredTerritoryFlag;
    string name;
    int reinforcementPool;
    std::vector<Player*> diplomaticAllies;
    int issueOrdersCount;
    static Player* neutralPlayer;
    std::vector<Territory*> territories;

    

 public:
  Player();
  Player(int nTerritories, int nCards, int nOrders);
  Player(string name);
  Player(const Player& player);
  ~Player();
  std::vector<Territory*> toDefend();
  std::vector<Territory*> toAttack();
  bool issueOrder();
  void testListOrder();
  Player& operator=(const Player& player);
  friend std::ostream& operator<<(std::ostream& strm, const Player& player);
  void addTerritory(Territory*);
  void addReinforcements(int);
  Hand* getHand();
  string getName();
  std::vector<Territory*> getTerritories();
  OrdersList* getOrderList();
  bool getConcqueredFlag();
  void setConcqueredFlag(bool flag);
  std::vector<Player*> getDiplomaticAllies();
  void addDiplomaticAlly(Player* ally);
  void clearDiplomaticAllies();
  std::vector<Territory*> createTerritoryList(int nTerritories);

};
