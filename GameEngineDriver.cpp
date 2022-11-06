#include "GameEngineDriver.h"

#include <iostream>
#include <string>

#include "GameEngine.h"

// Tests the GameEngine class
void testGameStates() {
  std::cout << "- Testing GameEngine: Copy Constructor\n";
  GameEngine* originalEngine = new GameEngine;
  originalEngine->setState(GameState::S_MAP_LOADED);
  std::cout << "Original Engine\n";
  std::cout << *originalEngine;
  GameEngine* copyEngine = originalEngine;
  std::cout << "Copy Engine\n";
  std::cout << *copyEngine;

  std::cout << "- Testing GameEngine: Assignment operator\n";
  originalEngine->handleCommand("validatemap");
  std::cout << "New Original Engine\n";
  std::cout << *originalEngine;
  copyEngine = originalEngine;
  std::cout << "New Copy Engine\n";
  std::cout << *copyEngine;

  std::cout << "- Testing GameEngine: Bad Command\n";
  copyEngine->handleCommand("extremely-bad-command-omg");

  delete copyEngine;

  std::cout << "- Testing GameEngine: Running Game States\n";
  GameEngine* runningGameEngine = new GameEngine;
  runningGameEngine->start();
  // while (runningGameEngine->getState() != GameState::S_END) {
  //   std::cout << *runningGameEngine;
  //   runningGameEngine->promptCommand();
  // }

  delete runningGameEngine;
}
