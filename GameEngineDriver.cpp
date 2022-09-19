#include "GameEngineDriver.h"

#include <iostream>

#include "GameEngine.h"

// Tests the GameEngine class
void testGameStates() {
  std::cout << "Testing Game States\n";
  GameEngine* gameEngine = new GameEngine;
  gameEngine->run();
}
