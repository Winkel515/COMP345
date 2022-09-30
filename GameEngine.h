#include <map>
#include <set>
#include <string>

namespace State {
enum StateEnum {
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

std::string getLabel(StateEnum);
};  // namespace State

namespace GameEngineUtils {
std::string promptCommand(std::set<std::string>);
void displayState(std::string);
void listCommands(std::set<std::string>);
}  // namespace GameEngineUtils

class GameEngineAssets {
 public:
  static const std::map<State::StateEnum, std::set<std::string>>
      validCommandsMap;
  static const std::map<std::string, State::StateEnum> desiredStateMap;
};

class GameEngine {
 private:
  State::StateEnum state;
  std::string command;
  void runHelper(State::StateEnum);
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
  State::StateEnum getState();
  void handleCommand(std::string);
  GameEngine();  // default constructor
};