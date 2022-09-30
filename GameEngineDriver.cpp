#include "GameEngineDriver.h"

#include <iostream>
#include <string>

#include "GameEngine.h"

// Tests the GameEngine class
void testGameStates() {
  std::cout << "Testing Game States\n";
  GameEngine* gameEngine = new GameEngine;
  gameEngine->start();

  while (gameEngine->getState() != GameState::S_END) {
    GameEngineUtils::displayState(GameState::getLabel(gameEngine->getState()));

    std::string command =
        GameEngineUtils::promptCommand(gameEngine->getValidCommands());

    gameEngine->handleCommand(command);
  }

  delete gameEngine;
}
