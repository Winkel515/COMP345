#pragma once

#include <iostream>
#include <list>
#include <string>
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "PlayerStrategies.h"

class Player {
  private:
    PlayerStrategy* strategy;
    std::vector<Territory*> territories;
    OrdersList* orders;
    Hand* cards;
    bool ConqueredTerritoryFlag;
    string name;
    int reinforcementPool;
    std::vector<Player*> diplomaticAllies;
    int issueOrdersCount;
    static Player* neutralPlayer;
    

 public:
  Player();
  Player(int nTerritories, int nCards, int nOrders);
  Player(string name);
  Player(string name, PlayerStrategy* strategy);
  Player(const Player& player);
  ~Player();
  std::vector<Territory*> toDefend(); //TODO: change for strategy
  std::vector<Territory*> toAttack(); //TODO: change for strategy
  bool issueOrder(); //TODO: change for strategy
  void testListOrder();
  Player& operator=(const Player& player);
  friend std::ostream& operator<<(std::ostream& strm, const Player& player);
  void addTerritory(Territory*);
  void addReinforcements(int);
  Hand* getHand();
  void setHand(Hand*);
  string getName();
  std::vector<Territory*> getTerritories();
  OrdersList* getOrderList();
  bool getConcqueredFlag();
  void setConcqueredFlag(bool flag);
  std::vector<Player*> getDiplomaticAllies();
  void addDiplomaticAlly(Player* ally);
  void clearDiplomaticAllies();
  std::vector<Territory*> createTerritoryList(int nTerritories);
  void setStrategy(PlayerStrategy* newStrategy);
  PlayerStrategy* getStrategy();
  std::vector<Territory*> getAdjacentTerritories();
  void removeTerritory(Territory*);
  void setTerritories(vector<Territory*>);
  int getReinforcements();
};
