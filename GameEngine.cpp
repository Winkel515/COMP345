#include "GameEngine.h"

#include <iostream>
#include <map>
#include <set>
#include <string>

using std::cin;
using std::cout;
using std::map;
using std::set;
using std::string;

using namespace GameState;

// Map from command to desired state
const map<string, GameStateEnum> GameEngineAssets::desiredStateMap{
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
const map<GameStateEnum, set<string>> GameEngineAssets::validCommandsMap{
    {S_START, {"loadmap"}},
    {S_MAP_LOADED, {"loadmap", "validatemap"}},
    {S_MAP_VALIDATED, {"addplayer"}},
    {S_PLAYERS_ADDED, {"addplayer", "assigncountries"}},
    {S_ASSIGN_REINFORCEMENT, {"issueorder"}},
    {S_ISSUE_ORDERS, {"issueorder", "endissueorders"}},
    {S_EXECUTE_ORDERS, {"execorder", "endexecorders", "win"}},
    {S_WIN, {"play", "end"}},
};

string GameState::getLabel(GameStateEnum state) {
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
  cout << "State at: " << state << "\n";
}

// Displays the list of valid commands
void GameEngineUtils::listCommands(set<string> validCommandsSet) {
  bool firstTime = true;
  std::cout << "List of available commands: {";

  for (set<string>::iterator i = validCommandsSet.begin();
       i != validCommandsSet.end(); i++) {
    if (!firstTime) {
      cout << ", ";
    } else {
      firstTime = false;
    }
    cout << *i;
  }

  cout << "}.\n";
}

// Prompts for the correct command
string GameEngineUtils::promptCommand(set<string> validCommandsSet) {
  string command = "";
  GameEngineUtils::listCommands(validCommandsSet);

  do {
    if (command != "" &&
        validCommandsSet.find(command) == validCommandsSet.end()) {
      cout << "Wrong command. Try again. \n";
    }
    cout << "Please enter a command: ";
    cin >> command;
  } while (validCommandsSet.find(command) == validCommandsSet.end());

  return command;
}

// Getter for state
GameStateEnum GameEngine::getState() { return this->state; }

// Default Constructor for GameEngine
GameEngine::GameEngine() { this->transition(S_START); }

// Change the values of the class according to new state
void GameEngine::transition(GameState::GameStateEnum state) {
  this->state = state;
  this->validCommands = GameEngineAssets::validCommandsMap.at(this->state);
}

// Runs the GameEngine
void GameEngine::start() {
  cout << "GameEngine launched\n";

  this->run();
}

// Single method to run the right function according to self state
void GameEngine::run() { this->runHelper(this->state); }

// Helps run the GameEngine by cascading to the right function
void GameEngine::runHelper(GameStateEnum state) {
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
bool GameEngine::handleCommand(string command) {
  // Checks if valid command
  // set<string> validCommands =
  // GameEngineAssets::validCommandsMap.at(this->state);

  // Transition the state
  GameStateEnum desiredState = GameEngineAssets::desiredStateMap.at(command);
  this->runHelper(desiredState);

  return true;
}

// Returns the list of valid commands
set<string> GameEngine::getValidCommands() { return this->validCommands; }

// Executes Start state
void GameEngine::execStart() {
  this->transition(S_START);
  // // Exec Start here
}

// Executes Map Loaded state
void GameEngine::execMapLoaded() {
  this->transition(S_MAP_LOADED);
  // // Exec Map loaded here
}

// Executes Map Validated state
void GameEngine::execMapValidated() {
  this->transition(S_MAP_VALIDATED);
  // // Exec Map Validated here
}

// Executes Players Added state
void GameEngine::execPlayersAdded() {
  this->transition(S_PLAYERS_ADDED);
  // // Exec Players Added here
}

// Executes Assign Reinforcement state
void GameEngine::execAssignReinforcement() {
  this->transition(S_ASSIGN_REINFORCEMENT);
  // // Exec Assign Reinforcement here
}

// Executes Issue Order state
void GameEngine::execIssueOrders() {
  this->transition(S_ISSUE_ORDERS);
  // // Exec Issue order here
}

// Execute Execute Orders state
void GameEngine::execExecuteOrders() {
  this->transition(S_EXECUTE_ORDERS);
  // // Exec Execute Orders here
}

// Execute Win state
void GameEngine::execWin() {
  this->transition(S_WIN);
  // // Exec Win here
}

void GameEngine::execEnd() {
  this->transition(S_END);
  // // Exec End here
  cout << "Game has ended.\n";
}
