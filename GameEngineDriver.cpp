#include "GameEngineDriver.h"

#include <iostream>
#include <string>

#include "GameEngine.h"

// Tests the GameEngine class
void testGameStates() {
  std::cout << "Testing Running Game States\n";
  GameEngine* runningGameEngine = new GameEngine;
  runningGameEngine->start();

  // Running prompt here:
  while (runningGameEngine->getState() != GameState::S_END) {
    std::cout << *runningGameEngine;
    runningGameEngine->promptCommand();
  }

  delete runningGameEngine;
}
