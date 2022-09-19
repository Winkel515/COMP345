#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

void displayState(string state) { std::cout << "State at: " << state << "\n"; }

// Displays the list of valid commands
void listCommands(set<string> validCommands) {
  bool firstTime = true;

  std::cout << "List of available commands: {";

  for (set<string>::iterator i = validCommands.begin();
       i != validCommands.end(); i++) {
    if (!firstTime) {
      std::cout << ", ";
    } else {
      firstTime = false;
    }

    std::cout << *i;
  }

  std::cout << "}.\n";
}

// Prompts for the correct command
string promptCommand(set<string> validCommands) {
  string command = "";
  listCommands(validCommands);

  do {
    if (command != "" && validCommands.find(command) == validCommands.end()) {
      std::cout << "Wrong command. Try again. \n";
    }
    std::cout << "Please enter a command: ";
    std::cin >> command;
  } while (validCommands.find(command) == validCommands.end());

  return command;
}

int main() {
  // Map to validate commands per state
  map<string, set<string>> validCommands;
  validCommands.insert(pair<string, set<string>>("start", {"loadmap"}));
  validCommands.insert(
      pair<string, set<string>>("map_loaded", {"loadmap", "validatemap"}));
  validCommands.insert(
      pair<string, set<string>>("map_validated", {"addplayer"}));
  validCommands.insert(pair<string, set<string>>(
      "players_added", {"addplayer", "assigncountries"}));
  validCommands.insert(
      pair<string, set<string>>("assign_reinforcement", {"issueorder"}));
  validCommands.insert(pair<string, set<string>>(
      "issue_orders", {"issueorder", "endissueorders"}));
  validCommands.insert(pair<string, set<string>>(
      "execute_orders", {"execorder", "endexecorders", "win"}));
  validCommands.insert(pair<string, set<string>>("win", {"play", "end"}));

  std::cout << "STARTUP\n";

  string state = "win";
  displayState(state);
  string command = promptCommand(validCommands.at(state));
  std::cout << "You entered: " << command << " \n";
}
