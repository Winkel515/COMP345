#include <iostream>

#include "CardsDriver.h"
#include "GameEngineDriver.h"
#include "MapDriver.h"
#include "PlayerDriver.h"

using std::cout;

int main() {
  cout << "====== Testing Map ======\n";
  testLoadMaps();
  cout << "====== Testing Players ======\n";
  testPlayers();
  cout << "====== Testing cards ======\n";
  testCards();
  cout << "====== Testing Game Engine ======\n";
  testGameStates();

  return 0;
}