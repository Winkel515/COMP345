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
std::string promptCommand(std::set<std::string>);
void displayState(std::string);
void listCommands(std::set<std::string>);
}  // namespace GameEngineUtils

class GameEngineAssets {
 public:
  static const std::map<GameState::GameStateEnum, std::set<std::string>>
      validCommandsMap;
  static const std::map<std::string, GameState::GameStateEnum> desiredStateMap;
};

class GameEngine {
 private:
  GameState::GameStateEnum state;
  std::set<std::string> validCommands;
  void runHelper(GameState::GameStateEnum);
  void transition(GameState::GameStateEnum);
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
  GameState::GameStateEnum getState();
  std::set<std::string> getValidCommands();
  bool handleCommand(std::string);
  GameEngine();  // default constructor
};