#include "Player.h"
#include "PlayerStrategies.h"
#include "GameEngine.h"
#include "CommandProcessing.h"



/*
MUST DEMONSTRATE:
(1) different players can be assigned different strategies that lead to different behavior using the Strategy design pattern; 
(2) the strategy adopted by a player can be changed dynamically during play, 
(3) the human player makes decisions according to user interaction, and computer players make decisions automatically, which are both implemented using the strategy pattern.
*/
void testPlayerStrategies(){

    //TODO: Create a game with Aggressive and neutral.

      // demonstrate that a the game engine works with order execution
  GameEngine* testEngine = new GameEngine();
  CommandProcessor* cp = testEngine->commandProcessor;

  cp->setNextInput("loadmap 3D.map");
  cp->getCommand();
  testEngine->setState(GameEngineFSA::commandToStateMap.at("loadmap"));
  cp->setNextInput("validatemap");
  cp->getCommand();
  testEngine->setState(GameEngineFSA::commandToStateMap.at("validatemap"));
  cp->setNextInput("addplayer a");
  cp->getCommand();
  cp->setNextInput("addplayer b");
  cp->getCommand();
  testEngine->setState(GameEngineFSA::commandToStateMap.at("addplayer"));
  // issue order command

  testEngine->players.at(0)->setStrategy(new AggressivePlayerStrategy(testEngine->players.at(0)));
  testEngine->players.at(1)->setStrategy(new NeutralPlayerStrategy(testEngine->players.at(1)));

  testEngine->startupPhase();
  testEngine->mainGameLoopTournament(20);

  delete testEngine;

    //TODO FOR DEMO: Show that the neutral player changes to aggressive when attacked -> make a human and attack neutral?
    //tournament with human and neutral, first attack neutral, next turn check neutral changed to aggressive

    //TODO: Create a second game with 1 human and 1 neutral to demonstrate human needs input, neutral doesn't. 

}