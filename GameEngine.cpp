#include "GameEngine.h"

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;
using namespace State;

// Map from command to desired state
const map<string, StateEnum> GameEngineAssets::desiredStateMap{
    {"loadmap", S_MAP_LOADED},
    {"validatemap", S_MAP_VALIDATED},
    {"addplayer", S_PLAYERS_ADDED},
    {"assigncountries", S_ASSIGN_REINFORCEMENT},
    {"issueorder", S_ISSUE_ORDERS},
    {"endissueorders", S_EXECUTE_ORDERS},
    {"execorder", S_EXECUTE_ORDERS},
    {"endexecorders", S_ASSIGN_REINFORCEMENT},
    {"win", S_WIN},
    {"play", S_START},
    {"end", S_END},
};

// Map from state to set of valid commands
const map<StateEnum, set<string>> GameEngineAssets::validCommandsMap{
    {S_START, {"loadmap"}},
    {S_MAP_LOADED, {"loadmap", "validatemap"}},
    {S_MAP_VALIDATED, {"addplayer"}},
    {S_PLAYERS_ADDED, {"addplayer", "assigncountries"}},
    {S_ASSIGN_REINFORCEMENT, {"issueorder"}},
    {S_ISSUE_ORDERS, {"issueorder", "endissueorders"}},
    {S_EXECUTE_ORDERS, {"execorder", "endexecorders", "win"}},
    {S_WIN, {"play", "end"}},
};

string State::getLabel(StateEnum state) {
  switch (state) {
    case S_START:
      return "Start";
      break;
    case S_MAP_LOADED:
      return "Map Loaded";
      break;
    case S_MAP_VALIDATED:
      return "Map Validated";
      break;
    case S_PLAYERS_ADDED:
      return "Players Added";
      break;
    case S_ASSIGN_REINFORCEMENT:
      return "Assign Reinforcement";
      break;
    case S_ISSUE_ORDERS:
      return "Issue Orders";
      break;
    case S_EXECUTE_ORDERS:
      return "Execute Orders";
      break;
    case S_WIN:
      return "Win";
      break;
    case S_END:
      return "End";
      break;
    default:
      return "Unknown State";
      break;
  }
};

// Displays the current state
void GameEngineUtils::displayState(string state) {
  std::cout << "State at: " << state << "\n";
}

// Displays the list of valid commands
void GameEngineUtils::listCommands(set<string> validCommandsSet) {
  bool firstTime = true;
  std::cout << "List of available commands: {";

  for (set<string>::iterator i = validCommandsSet.begin();
       i != validCommandsSet.end(); i++) {
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
string GameEngineUtils::promptCommand(set<string> validCommandsSet) {
  string command = "";
  GameEngineUtils::listCommands(validCommandsSet);

  do {
    if (command != "" &&
        validCommandsSet.find(command) == validCommandsSet.end()) {
      std::cout << "Wrong command. Try again. \n";
    }
    std::cout << "Please enter a command: ";
    std::cin >> command;
  } while (validCommandsSet.find(command) == validCommandsSet.end());

  return command;
}

// Getter for state
StateEnum GameEngine::getState() { return this->state; }

// Default Constructor for GameEngine
GameEngine::GameEngine() {
  this->state = S_START;
  this->command = "";
}

// Runs the GameEngine
void GameEngine::start() {
  std::cout << "GameEngine launched\n";

  this->runHelper(this->state);
}

// Helps run the GameEngine by directing to the right function
void GameEngine::runHelper(StateEnum state) {
  switch (state) {
    case S_START:
      this->execStart();
      break;
    case S_MAP_LOADED:
      this->execMapLoaded();
      break;
    case S_MAP_VALIDATED:
      this->execMapValidated();
      break;
    case S_PLAYERS_ADDED:
      this->execPlayersAdded();
      break;
    case S_ASSIGN_REINFORCEMENT:
      this->execAssignReinforcement();
      break;
    case S_ISSUE_ORDERS:
      this->execIssueOrders();
      break;
    case S_EXECUTE_ORDERS:
      this->execExecuteOrders();
      break;
    case S_WIN:
      this->execWin();
      break;
    case S_END:
      this->execEnd();
      break;
    default:
      break;
  }
}

// Handles the mapping between command and state
void GameEngine::handleCommand(std::string command) {
  StateEnum desiredState = GameEngineAssets::desiredStateMap.at(command);
  this->runHelper(desiredState);
}

// Executes Start state
void GameEngine::execStart() {
  this->state = S_START;
  // GameEngineUtils::displayState(getLabel(this->state));
  // // Exec Start here
  // this->command = GameEngineUtils::promptCommand(
  //     GameEngineAssets::validCommandsMap.at(this->state));
  // this->handleCommand(this->command);
}

// Executes Map Loaded state
void GameEngine::execMapLoaded() {
  this->state = S_MAP_LOADED;
  // GameEngineUtils::displayState(getLabel(this->state));
  // // Exec Map loaded here
  // this->command = GameEngineUtils::promptCommand(
  //     GameEngineAssets::validCommandsMap.at(this->state));
  // this->handleCommand(this->command);
}

// Executes Map Validated state
void GameEngine::execMapValidated() {
  this->state = S_MAP_VALIDATED;
  // GameEngineUtils::displayState(getLabel(this->state));
  // // Exec Map Validated here
  // this->command = GameEngineUtils::promptCommand(
  //     GameEngineAssets::validCommandsMap.at(this->state));
  // this->handleCommand(this->command);
}

// Executes Players Added state
void GameEngine::execPlayersAdded() {
  this->state = S_PLAYERS_ADDED;
  // GameEngineUtils::displayState(getLabel(this->state));
  // // Exec Players Added here
  // this->command = GameEngineUtils::promptCommand(
  //     GameEngineAssets::validCommandsMap.at(this->state));
  // this->handleCommand(this->command);
}

// Executes Assign Reinforcement state
void GameEngine::execAssignReinforcement() {
  this->state = S_ASSIGN_REINFORCEMENT;
  // GameEngineUtils::displayState(getLabel(this->state));
  // // Exec Assign Reinforcement here
  // this->command = GameEngineUtils::promptCommand(
  //     GameEngineAssets::validCommandsMap.at(this->state));
  // this->handleCommand(this->command);
}

// Executes Issue Order state
void GameEngine::execIssueOrders() {
  this->state = S_ISSUE_ORDERS;
  // GameEngineUtils::displayState(getLabel(this->state));
  // // Exec Issue order here
  // this->command = GameEngineUtils::promptCommand(
  //     GameEngineAssets::validCommandsMap.at(this->state));
  // this->handleCommand(this->command);
}

// Execute Execute Orders state
void GameEngine::execExecuteOrders() {
  this->state = S_EXECUTE_ORDERS;
  // GameEngineUtils::displayState(getLabel(this->state));
  // // Exec Execute Orders here
  // this->command = GameEngineUtils::promptCommand(
  //     GameEngineAssets::validCommandsMap.at(this->state));
  // this->handleCommand(this->command);
}

// Execute Win state
void GameEngine::execWin() {
  this->state = S_WIN;
  // GameEngineUtils::displayState(getLabel(this->state));
  // // Exec Win here
  // this->command = GameEngineUtils::promptCommand(
  //     GameEngineAssets::validCommandsMap.at(this->state));
  // this->handleCommand(this->command);
}

void GameEngine::execEnd() {
  this->state = S_END;
  std::cout << "Game has ended.\n";
}
