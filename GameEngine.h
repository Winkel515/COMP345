#include <iostream>
#include <map>
#include <set>
#include <string>

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

namespace GameEngineUtils {
void displayState(std::string);
}  // namespace GameEngineUtils

class GameEngineFSA {
 public:
  static const std::map<GameState::GameStateEnum, std::set<std::string>>
      commandsPerStateMap;
  static const std::map<std::string, GameState::GameStateEnum>
      commandToStateMap;
};

class GameEngine {
 private:
  GameState::GameStateEnum state;
  std::set<std::string> commands;
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

 public:
  void start();
  void run();
  bool handleCommand(std::string);
  void promptCommand();
  void printCommands();
  std::set<std::string> getCommands();
  void setState(GameState::GameStateEnum);
  GameState::GameStateEnum getState();
  GameEngine& operator=(const GameEngine&);
  GameEngine();                   // default constructor
  GameEngine(const GameEngine&);  // copy constructor
  friend std::ostream& operator<<(std::ostream&,
                                  const GameEngine&);  // stream insertion
};