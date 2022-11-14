#include "GameEngineDriver.h"

#include <iostream>
#include <string>

#include "CommandProcessing.h"
#include "GameEngine.h"
#include "LoggingObserver.h"

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

  // std:cout << "- Testing GameEngine: with file\n";
  // GameEngine* fileGameEngine = new GameEngine;
  // fileGameEngine->setCommandProcessor(new FileCommandProcessorAdapter("testcommands.txt"));
  // fileGameEngine->start();

  std::cout << "- Testing GameEngine: Running Game States\n";
  GameEngine* runningGameEngine = new GameEngine;
  runningGameEngine->start();
  while (runningGameEngine->getState() != GameState::S_END) {
    std::cout << *runningGameEngine;
    runningGameEngine->promptCommand();
  }

  // delete fileGameEngine;
  delete runningGameEngine;
}

// Tests main game loop function
void testMainGameLoop() {
  GameEngine* testEngine = new GameEngine();
  CommandProcessor* cp = testEngine->commandProcessor;
  
  cp->setNextInput("loadmap 3D.map");
  cp->getCommand();
  cp->setNextInput("validatemap");
  cp->getCommand();
  cp->setNextInput("addplayer a");
  cp->getCommand();
  cp->setNextInput("addplayer b");
  cp->getCommand();
  cp->setNextInput("gamestart");
  cp->getCommand();
  testEngine->mainGameLoop();

  delete testEngine;

  // receive correct number of units during reinforcements
  // issue only deploy orders if they still have reinforcements
  // issue atttack/defend orders
  // issue card orders
  // removing player from game (no territories)
  // game ends 
}

void testStartupPhase(){
  GameEngine* testEngine = new GameEngine();
  testEngine->startupPhase();
  delete testEngine;
}
