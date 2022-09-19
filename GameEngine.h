#include <map>
#include <set>
#include <string>

class GameEngineAssets {
 public:
  static const std::map<std::string, std::set<std::string>> validCommandsMap;
};

namespace GameEngineUtils {
std::string promptCommand(std::set<std::string>);
void displayState(std::string);
void listCommands(std::set<std::string>);

}  // namespace GameEngineUtils

class GameEngine {
 public:
  // static std::string promptCommand(std::set<std::string> validCommands);
};