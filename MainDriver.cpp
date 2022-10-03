#include <iostream>
#include "MapDriver.h"
#include "CardsDriver.h"

#include "GameEngineDriver.h"

using std::cout;

int main() {
  cout << "====== Testing Map ======\n";
  testLoadMaps();
  cout << "====== Testing cards ======\n";
  testCards();
  cout << "====== Testing Game Engine ======\n";
  testGameStates();

  

  return 0;
}