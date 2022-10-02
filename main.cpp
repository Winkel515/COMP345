#include <iostream>

#include "Player.h"
#include "PlayerDriver.h"

int main() {
  Player* p1 = new Player();
  std::cout << *p1;

  // testPlayers();

  return 0;
}