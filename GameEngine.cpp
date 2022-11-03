#include "GameEngine.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>

using std::cin;
using std::cout;
using std::map;
using std::ostream;
using std::set;
using std::string;

using namespace GameState;

// Map from command to desired state
const map<string, GameStateEnum> GameEngineFSA::commandToStateMap{
    {"loadmap", S_MAP_LOADED},
    {"validatemap", S_MAP_VALIDATED},
    {"addplayer", S_PLAYERS_ADDED},
    {"gamestart", S_ASSIGN_REINFORCEMENT},
    // {"assigncountries", S_ASSIGN_REINFORCEMENT},
    {"issueorder", S_ISSUE_ORDERS},
    {"endissueorders", S_EXECUTE_ORDERS},
    {"execorder", S_EXECUTE_ORDERS},
    {"endexecorders", S_ASSIGN_REINFORCEMENT},
    {"win", S_WIN},
    {"play", S_START},
    {"end", S_END},
};

// Map from state to set of valid commands
const map<GameStateEnum, set<string>> GameEngineFSA::commandsPerStateMap{
    {S_START, {"loadmap"}},
    {S_MAP_LOADED, {"loadmap", "validatemap"}},
    {S_MAP_VALIDATED, {"addplayer"}},
    {S_PLAYERS_ADDED, {"addplayer", "gamestart"}},
    // {S_PLAYERS_ADDED, {"addplayer", "assigncountries"}},
    {S_ASSIGN_REINFORCEMENT, {"issueorder"}},
    {S_ISSUE_ORDERS, {"issueorder", "endissueorders"}},
    {S_EXECUTE_ORDERS, {"execorder", "endexecorders", "win"}},
    {S_WIN, {"play", "end"}},
};

// Returns a string label from a GameStateEnum
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

// Default Constructor for GameEngine
GameEngine::GameEngine() { setState(S_START); }

// Copy Constructor for GameEngine
GameEngine::GameEngine(const GameEngine &ge) { setState(ge.state); }

// Assignment Operator for GameEngine
GameEngine &GameEngine::operator=(const GameEngine &copy) {
  setState(copy.state);
  return *this;
}

GameEngine::~GameEngine() {
  if (mapLoader != NULL) delete mapLoader;
}

// Overload Stream insertion
ostream &operator<<(ostream &out, const GameEngine &gameEngine) {
  out << "Game Engine ";
  out << "State: " << GameState::getLabel(gameEngine.state) << "\n";
  out << "Available commands: ";

  bool firstTime_noComma = true;

  for (set<string>::iterator i = gameEngine.commands.begin();
       i != gameEngine.commands.end(); i++) {
    if (!firstTime_noComma) {
      out << ", ";
    } else {
      firstTime_noComma = false;
    }
    out << *i;
  }

  out << ".\n";

  return out;
}

// Getter for state
GameStateEnum GameEngine::getState() { return this->state; }

// Change the values of the class according to new state
void GameEngine::setState(GameState::GameStateEnum state) {
  this->state = state;
  if (state == S_END) {
    commands = {""};
  } else {
    commands = GameEngineFSA::commandsPerStateMap.at(this->state);
  }
}

// Runs the GameEngine
void GameEngine::start() {
  cout << "GameEngine launched\n";

  run();
}

// Single method to run the right function according to self state
void GameEngine::run() { this->execSelector(this->state); }

// Helps run the GameEngine by cascading to the right function
void GameEngine::execSelector(GameStateEnum state) {
  switch (state) {
    case S_START:
      startupPhase();
      break;
    case S_MAP_LOADED:
      execMapLoaded();
      break;
    case S_MAP_VALIDATED:
      execMapValidated();
      break;
    case S_PLAYERS_ADDED:
      execPlayersAdded();
      break;
    case S_ASSIGN_REINFORCEMENT:
      execAssignReinforcement();
      break;
    case S_ISSUE_ORDERS:
      execIssueOrders();
      break;
    case S_EXECUTE_ORDERS:
      execExecuteOrders();
      break;
    case S_WIN:
      execWin();
      break;
    case S_END:
      execEnd();
      break;
    default:
      break;
  }
}

// Prompts for the command
vector<string> GameEngine::promptCommand() {
  string command = "";

  do {
    if (command != "" && commands.find(command) == commands.end()) {
      cout << "Try again.\n";
    }
    cout << "Please enter a command: ";
    getline(cin, command);
  } while (!handleCommand(command, true));

  return splitString(command, " ");
}

vector<string> GameEngine::promptCommand(bool transitionState) {
  string command = "";

  do {
    if (command != "" && commands.find(command) == commands.end()) {
      cout << "Try again.\n";
    }
    cout << "Please enter a command: ";
    getline(cin, command);
  } while (!handleCommand(command, transitionState));

  return splitString(command, " ");
}

// Displays the list of valid commands
void GameEngine::printCommands() {
  bool firstTime_noComma = true;
  std::cout << "List of available commands: ";

  for (set<string>::iterator i = commands.begin(); i != commands.end(); i++) {
    if (!firstTime_noComma) {
      cout << ", ";
    } else {
      firstTime_noComma = false;
    }
    cout << *i;
  }

  cout << ".\n";
}

// Handles the mapping between command and state
bool GameEngine::handleCommand(string command) {
  command = splitString(command, " ").at(0);
  // Checks if valid command
  if (commands.find(command) == commands.end()) {
    cout << "Invalid Command.\n";
    return false;
  }

  // Transition the state
  GameStateEnum desiredState = GameEngineFSA::commandToStateMap.at(command);
  setState(desiredState);

  return true;
}

bool GameEngine::handleCommand(string command, bool transitionState) {
  command = splitString(command, " ").at(0);
  // Checks if valid command
  if (commands.find(command) == commands.end()) {
    cout << "Invalid Command.\n";
    return false;
  }

  if (transitionState) {
    GameStateEnum desiredState = GameEngineFSA::commandToStateMap.at(command);
    setState(desiredState);
  }

  return true;
}

// Returns the list of valid commands
set<string> GameEngine::getCommands() { return commands; }

// Executes Start state
void GameEngine::execStart() {
  // // Exec Start here
}

// Executes Map Loaded state
void GameEngine::execMapLoaded() {
  // // Exec Map loaded here
}

// Executes Map Validated state
void GameEngine::execMapValidated() {
  // // Exec Map Validated here
}

// Executes Players Added state
void GameEngine::execPlayersAdded() {
  // // Exec Players Added here
}

// Executes Assign Reinforcement state
void GameEngine::execAssignReinforcement() {
  // // Exec Assign Reinforcement here
}

// Executes Issue Order state
void GameEngine::execIssueOrders() {
  // // Exec Issue order here
}

// Execute Execute Orders state
void GameEngine::execExecuteOrders() {
  // // Exec Execute Orders here
}

// Execute Win state
void GameEngine::execWin() {
  // // Exec Win here
}

// Execute End state
void GameEngine::execEnd() {
  // // Exec End here
  cout << "Game has ended.\n";
}

void GameEngine::startupPhase() {
  // S_START state loading a map
  while (true) {
    printCommands();
    vector<string> result = promptCommand(false);
    mapLoader = new MapLoader();
    if (result.size() <= 1)
      cout << "Enter a file name in the format loadmap <filename>" << std::endl;
    else if (mapLoader->loadMap(result.at(1))) {
      cout << "\"" << result.at(1) << "\" has been loaded\n";
      setState(GameEngineFSA::commandToStateMap.at("loadmap"));
      break;
    }
  }

  // S_MAP_LOADED state, load map or validate map
  // transition to S_MAP_VALIDATED validate is successful
  while (true) {
    printCommands();
    vector<string> result = promptCommand(false);

    // 2 possible commands: loadmap/validatemap
    if (result.at(0) == "loadmap") {
      if (result.size() <= 1)
        cout << "Enter a file name in the format loadmap <filename>"
             << std::endl;
      else if (mapLoader->loadMap(result.at(1))) {
        cout << "\"" << result.at(1) << "\" has been loaded\n";
      }
    }

    else if (result.at(0) == "validatemap") {
      if (mapLoader->getMap()->validate()) {
        cout << "The map passed all the tests and is a valid map to be used.\n";
        setState(GameEngineFSA::commandToStateMap.at("validatemap"));
        break;
      } else {
        cout << "The map has failed at least one test and is not a valid map. "
                "Try loading another map.\n";
      }
    }
  }

  // addPlayer implementation:
  bool done_adding_players = false;
  int nPlayers = 0;
  cout << "Enter 2-6 players in the format \"addplayer <playername>\"" << endl;
  cout << "When you have added all players, start game with \"gamestart\" "
          "command"
       << endl;

  while (!done_adding_players) {
    printCommands();
    vector<string> result = promptCommand(false);

    if (result.at(0) == "addplayer") {
      if (result.size() <= 1) {
        cout << "Specify the player name in the format \"addplayer "
                "<playername>\""
             << endl;
        continue;
      }
      players.push_back(new Player(result.at(1)));
      nPlayers++;
    } else if (result.at(0) ==
               "assigncountries") {  // TODO: Change this to gamestart, once
                                     // it's been changed in FSA
      done_adding_players = true;
    }

    // Allow gamestart command once we have added 2 players.
    if (nPlayers == 2) {
      setState(GameEngineFSA::commandToStateMap.at("addplayer"));
    }

    if (nPlayers == 6) {
      cout << "The maximum number of players have been added. Game will start "
              "now."
           << endl;
      done_adding_players = true;
    }
    if (done_adding_players)
      // TODO: Change to "gamestart" whenever changed in FSA
      setState(GameEngineFSA::commandToStateMap.at("assigncountries"));
  }

  // gamestart phase:

  // TODO: Set territory owners in distributeTerritories
  mapLoader->getMap()->distributeTerritories(players);

  //  Randomly shuffle player vector to determine player order.
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(this->players.begin(), this->players.end(),
          std::default_random_engine(seed));

  // TODO: Should this be initialized in GameEngine constructor?
  deck = new Deck(3);
  // Each player gets 50 reincforcements and draws 2 cards
  for (int i = 0; i < players.size(); i++) {
    players.at(i)->addReinforcements(50);
    players.at(i)->getHand()->drawCard(deck);
    players.at(i)->getHand()->drawCard(deck);
  }

  for (int i = 0; i < players.size(); i++) {
    cout << "Player " << i + 1 << ": " << *players.at(i) << endl;
  }
}