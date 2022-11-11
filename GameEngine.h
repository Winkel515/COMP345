#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <map>
#include <set>
#include <string>


#include "LoggingObserver.h"
#include "Cards.h"
#include "Map.h"
#include "Player.h"

class CommandProcessor;

namespace GameState {
enum GameStateEnum {
  S_START,
  S_MAP_LOADED,
  S_MAP_VALIDATED,
  S_PLAYERS_ADDED,
  S_ASSIGN_REINFORCEMENT,
  S_ISSUE_ORDERS,
  S_EXECUTE_ORDERS,
  S_WIN,
  S_END
};

std::string getLabel(GameStateEnum);
};  // namespace GameState

class GameEngineFSA {
 public:
  static const std::map<GameState::GameStateEnum, std::set<std::string>>
      commandsPerStateMap;
  static const std::map<std::string, GameState::GameStateEnum>
      commandToStateMap;
};

class GameEngine : public Subject, public ILoggable {
 private:
  // Attributes
  GameState::GameStateEnum state;
  std::set<std::string> commands;
  std::vector<Player*> players;
  Deck* deck;
  MapLoader* mapLoader;
  CommandProcessor* commandProcessor;

  // Methods
  void execSelector(GameState::GameStateEnum);
  void execStart();
  void execMapLoaded();
  void execMapValidated();
  void execPlayersAdded();
  void execAssignReinforcement();
  void execIssueOrders();
  void execExecuteOrders();
  void execWin();
  void execEnd();
  void startupPhase();

 public:
  void start();
  void run();
  bool handleCommand(std::string);
  bool handleCommand(std::string, bool);
  std::vector<std::string> promptCommand();
  std::vector<std::string> promptCommand(bool);
  void printCommands();
  std::set<std::string> getCommands();
  void setState(GameState::GameStateEnum);
  GameState::GameStateEnum getState();
  GameEngine& operator=(const GameEngine&);
  GameEngine();                   // default constructor
  GameEngine(const GameEngine&);  // copy constructor
  ~GameEngine();
  string stringToLog();
  friend std::ostream& operator<<(std::ostream&,
                                  const GameEngine&);  // stream insertion
};

#endif