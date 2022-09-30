#include "GameEngineDriver.h"

#include <iostream>
#include <string>

#include "GameEngine.h"

// Tests the GameEngine class
void testGameStates() {
  std::cout << "Testing Game States\n";
  GameEngine* gameEngine = new GameEngine;
  gameEngine->start();

  while (gameEngine->getState() != State::S_END) {
    GameEngineUtils::displayState(State::getLabel(gameEngine->getState()));

    std::string command = GameEngineUtils::promptCommand(
        GameEngineAssets::validCommandsMap.at(gameEngine->getState()));

    gameEngine->handleCommand(command);
  }

  delete gameEngine;
}
