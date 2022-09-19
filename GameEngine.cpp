#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

void displayState(string state) { std::cout << "State at: " << state << "\n"; }

void promptCommand(set<string> validCommands) {
  for (set<string>::iterator i = validCommands.begin();
       i != validCommands.end(); i++) {
    std::cout << *i << "\n";
  }
}

int main() {
  // Map to validate commands per state
  map<string, set<string>> validCommandsMap;
  validCommandsMap.insert(pair<string, set<string>>("start", {"loadmap"}));
  validCommandsMap.insert(
      pair<string, set<string>>("map_loaded", {"loadmap", "validatemap"}));
  validCommandsMap.insert(
      pair<string, set<string>>("map_validated", {"addplayer"}));
  validCommandsMap.insert(pair<string, set<string>>(
      "players_added", {"addplayer", "assigncountries"}));
  validCommandsMap.insert(
      pair<string, set<string>>("assign_reinforcement", {"issueorder"}));
  validCommandsMap.insert(pair<string, set<string>>(
      "issue_orders", {"issueorder", "endissueorders"}));
  validCommandsMap.insert(pair<string, set<string>>(
      "execute_orders", {"execorder", "endexecorders", "win"}));
  validCommandsMap.insert(pair<string, set<string>>("win", {"play", "end"}));
  std::cout << "STARTUP";

  string state = "win";
  displayState(state);
  promptCommand(validCommandsMap.at(state));
}
