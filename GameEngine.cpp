#include "GameEngine.h"

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

const map<string, string> GameEngineAssets::desiredStateMap{
    {"loadmap", "map_loaded"},
    {"validatemap", "map_validated"},
    {"addplayer", "players_added"},
    {"assigncountries", "assign_reinforcement"},
    {"issueorder", "issue_orders"},
    {"endissueorders", "execute_orders"},
    {"execorder", "execute_orders"},
    {"endexecorders", "assign_reinforcement"},
    {"win", "win"},
    {"play", "start"},
    {"end", "end"},
};

const map<string, set<string>> GameEngineAssets::validCommandsMap{
    {"start", {"loadmap"}},
    {"map_loaded", {"loadmap", "validatemap"}},
    {"map_validated", {"addplayer"}},
    {"players_added", {"addplayer", "assigncountries"}},
    {"assign_reinforcement", {"issueorder"}},
    {"issue_orders", {"issueorder", "endissueorders"}},
    {"execute_orders", {"execorder", "endexecorders", "win"}},
    {"win", {"play", "end"}},
};

void GameEngineUtils::displayState(string state) {
  std::cout << "State at: " << state << "\n";
}

// Displays the list of valid commands
void GameEngineUtils::listCommands(set<string> validCommands) {
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

// Default Constructor for GameEngine
GameEngine::GameEngine() {
  this->state = "start";
  this->command = "";
}

void GameEngine::run() {
  std::cout << "GameEngine launched\n";
  std::cout << this->state << "\n";
}

// Prompts for the correct command
string GameEngineUtils::promptCommand(set<string> validCommands) {
  string command = "";
  GameEngineUtils::listCommands(validCommands);

  do {
    if (command != "" && validCommands.find(command) == validCommands.end()) {
      std::cout << "Wrong command. Try again. \n";
    }
    std::cout << "Please enter a command: ";
    std::cin >> command;
  } while (validCommands.find(command) == validCommands.end());

  return command;
}

// int main() {
//   std::cout << "STARTUP\n";
//   string state = "";
//   string command = "";

//   do {
//     // start state
//     state = "start";
//     GameEngineUtils::displayState(state);
//     command = GameEngineUtils::promptCommand(
//         GameEngineAssets::validCommandsMap.at(state));

//     // -> Entered loadmap
//     // map_loaded state
//     do {
//       state = "map_loaded";
//       GameEngineUtils::displayState(state);
//       command = GameEngineUtils::promptCommand(
//           GameEngineAssets::validCommandsMap.at(state));
//     } while (command == "loadmap");

//     // -> Entered validatemap
//     // map_validated state
//     state = "map_validated";
//     GameEngineUtils::displayState(state);
//     command = GameEngineUtils::promptCommand(
//         GameEngineAssets::validCommandsMap.at(state));

//     // -> Entered addplayer
//     do {
//       state = "players_added";
//       GameEngineUtils::displayState(state);
//       command = GameEngineUtils::promptCommand(
//           GameEngineAssets::validCommandsMap.at(state));
//     } while (command == "addplayer");

//     // -> From execute_orders, Entered endexecorders
//     do {
//       // -> Entered assigncountries
//       state = "assign_reinforcement";
//       GameEngineUtils::displayState(state);
//       command = GameEngineUtils::promptCommand(
//           GameEngineAssets::validCommandsMap.at(state));

//       // -> Entered issueorder
//       do {
//         state = "issue_orders";
//         GameEngineUtils::displayState(state);
//         command = GameEngineUtils::promptCommand(
//             GameEngineAssets::validCommandsMap.at(state));
//       } while (command == "issueorder");

//       // -> Entered endissueorders
//       do {
//         state = "execute_orders";
//         GameEngineUtils::displayState(state);
//         command = GameEngineUtils::promptCommand(
//             GameEngineAssets::validCommandsMap.at(state));
//       } while (command == "execorder");

//     } while (command == "endexecorders");

//     state = "win";
//     GameEngineUtils::displayState(state);
//     command = GameEngineUtils::promptCommand(
//         GameEngineAssets::validCommandsMap.at(state));
//   } while (command == "play");

//   std::cout << "GAME HAS ENDED\n";
// }
