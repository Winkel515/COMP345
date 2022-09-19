#include <map>
#include <set>
#include <string>

namespace GameEngineUtils {
std::string promptCommand(std::set<std::string>);
void displayState(std::string);
void listCommands(std::set<std::string>);
}  // namespace GameEngineUtils

class GameEngineAssets {
 public:
  static const std::map<std::string, std::set<std::string>> validCommandsMap;
  static const std::map<std::string, std::string> desiredStateMap;
};

class GameEngine {
 private:
  std::string state;
  std::string command;
  void runHelper(std::string);
  void handleCommand(std::string);
  void execStart();
  void execMapLoaded();
  void execMapValidated();
  void execPlayersAdded();
  void execAssignReinforcement();
  void execIssueOrders();
  void execExecuteOrders();
  void execWin();

 public:
  void run();
  GameEngine();  // default constructor
};