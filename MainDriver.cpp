#include <iostream>

#include "CardsDriver.h"
#include "GameEngineDriver.h"
#include "MapDriver.h"
#include "OrdersDriver.h"
#include "PlayerDriver.h"

using std::cout;

int main() {
  cout << "====== Testing Map ======\n";
  testLoadMaps();
  cout << "====== Testing Players ======\n";
  testPlayers();
  cout << "====== Testing Cards ======\n";
  testCards();
  cout << "====== Testing Orders ======\n";
  testOrdersList();
  cout << "====== Testing Game Engine ======\n";
  testGameStates();

  return 0;
}