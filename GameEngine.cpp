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

// Displays the current state
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

// Default Constructor for GameEngine
GameEngine::GameEngine() {
  this->state = "start";
  this->command = "";
}

// Runs the GameEngine
void GameEngine::run() {
  std::cout << "GameEngine launched\n";

  this->runHelper(this->state);
}

// Helps run the GameEngine by directing to the right function
void GameEngine::runHelper(std::string state) {
  if (state == "start") {
    this->execStart();
  } else if (state == "map_loaded") {
    this->execMapLoaded();
  } else if (state == "map_validated") {
    this->execMapValidated();
  } else if (state == "players_added") {
    this->execPlayersAdded();
  } else if (state == "assign_reinforcement") {
    this->execAssignReinforcement();
  } else if (state == "issue_orders") {
    this->execIssueOrders();
  } else if (state == "execute_orders") {
    this->execExecuteOrders();
  } else if (state == "win") {
    this->execWin();
  } else {
    std::cout << "Game has ended.\n";
  }
}

// Handles the mapping between command and state
void GameEngine::handleCommand(std::string command) {
  string desiredState = GameEngineAssets::desiredStateMap.at(command);
  this->runHelper(desiredState);
}

// Executes Start state
void GameEngine::execStart() {
  this->state = "start";
  GameEngineUtils::displayState(this->state);
  this->command = GameEngineUtils::promptCommand(
      GameEngineAssets::validCommandsMap.at(this->state));
  this->handleCommand(this->command);
}

// Executes Map Loaded state
void GameEngine::execMapLoaded() {
  this->state = "map_loaded";
  GameEngineUtils::displayState(this->state);
  this->command = GameEngineUtils::promptCommand(
      GameEngineAssets::validCommandsMap.at(this->state));
  this->handleCommand(this->command);
}

// Executes Map Validated state
void GameEngine::execMapValidated() {
  this->state = "map_validated";
  GameEngineUtils::displayState(this->state);
  this->command = GameEngineUtils::promptCommand(
      GameEngineAssets::validCommandsMap.at(this->state));
  this->handleCommand(this->command);
}

// Executes Players Added state
void GameEngine::execPlayersAdded() {
  this->state = "players_added";
  GameEngineUtils::displayState(this->state);
  this->command = GameEngineUtils::promptCommand(
      GameEngineAssets::validCommandsMap.at(this->state));
  this->handleCommand(this->command);
}

// Executes Assign Reinforcement state
void GameEngine::execAssignReinforcement() {
  this->state = "assign_reinforcement";
  GameEngineUtils::displayState(this->state);
  this->command = GameEngineUtils::promptCommand(
      GameEngineAssets::validCommandsMap.at(this->state));
  this->handleCommand(this->command);
}

// Executes Issue Order state
void GameEngine::execIssueOrders() {
  this->state = "issue_orders";
  GameEngineUtils::displayState(this->state);
  this->command = GameEngineUtils::promptCommand(
      GameEngineAssets::validCommandsMap.at(this->state));
  this->handleCommand(this->command);
}

// Execute Execute Orders state
void GameEngine::execExecuteOrders() {
  this->state = "execute_orders";
  GameEngineUtils::displayState(this->state);
  this->command = GameEngineUtils::promptCommand(
      GameEngineAssets::validCommandsMap.at(this->state));
  this->handleCommand(this->command);
}

// Execute Win state
void GameEngine::execWin() {
  this->state = "win";
  GameEngineUtils::displayState(this->state);
  this->command = GameEngineUtils::promptCommand(
      GameEngineAssets::validCommandsMap.at(this->state));
  this->handleCommand(this->command);
}
