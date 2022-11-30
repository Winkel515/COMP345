#include "GameEngine.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>

#include "CommandProcessing.h"
#include "LoggingObserver.h"

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
GameEngine::GameEngine() : GameEngine(new CommandProcessor()) {}

// Constructor with command processor
GameEngine::GameEngine(CommandProcessor *cProcessor) {
  setState(S_START);
  mapLoader = new MapLoader();
  setCommandProcessor(cProcessor);
  logObserver = new LogObserver();
  commandProcessor->Attach(logObserver);
  // LogObserver *commandProcessorView = new LogObserver(commandProcessor);
  deck = new Deck(3);
}

// Copy Constructor for GameEngine
GameEngine::GameEngine(const GameEngine &ge) {
  setState(ge.state);
  mapLoader = new MapLoader(*ge.mapLoader);
  commandProcessor = new CommandProcessor(&commands);
  logObserver = new LogObserver();
  commandProcessor->Attach(logObserver);
  // LogObserver *commandProcessorView = new LogObserver(commandProcessor);
  deck = new Deck(3);
}

void GameEngine::setCommandProcessor(CommandProcessor *cProcessor) {
  this->commandProcessor = cProcessor;
  commandProcessor->initValidCommandsPtr(&commands);
}

// Assignment Operator for GameEngine
GameEngine &GameEngine::operator=(const GameEngine &copy) {
  setState(copy.state);
  return *this;
}

GameEngine::~GameEngine() {
  delete mapLoader;
  delete commandProcessor;
  delete logObserver;
  for (int i = 0; i < players.size(); i++) delete players.at(i);
  delete deck;
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

// Change the values of the class according to new state - transition function
void GameEngine::setState(GameState::GameStateEnum state) {
  this->state = state;
  if (state == S_END) {
    commands = {""};
  } else {
    commands = GameEngineFSA::commandsPerStateMap.at(this->state);
  }
  Notify(this);
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
      reinforcementPhase();
      break;
    case S_ISSUE_ORDERS:
      issueOrdersPhase();
      break;
    case S_EXECUTE_ORDERS:
      executeOrdersPhase();
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

void printCommands(set<string> &commands) {
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
    cout << command << "is invalid Command.\n";
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
    cout << command << " is an invalid command.\n";
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
  // // Exec Players Added here. Add 2 players.
}

// Executes Assign Reinforcement state
void GameEngine::reinforcementPhase() {
  // // Exec Assign Reinforcement here
  for (int i = 0; i < players.size(); i++) {
    // Get reinforcement for Player
    int reinforcements;
    reinforcements = (int)(players.at(i)->getTerritories().size()) / 3;

    // Territoy list from player
    std::vector<Territory *> playerList = players.at(i)->getTerritories();

    // Territoy list from map
    std::vector<string> continentList =
        mapLoader->getMap()->getContinentsNames();
    std::vector<Territory *> territoryList =
        mapLoader->getMap()->getTerritories();

    // Erase all territories in territory list that exist in player list
    for (int j = 0; j < playerList.size(); j++) {
      for (int k = 0; k < territoryList.size(); k++) {
        if (playerList.at(j)->getName() == territoryList.at(k)->getName()) {
          territoryList.erase(territoryList.begin() + k);
        }
      }
    }

    // Erase all continents in continent list that exist in territory list
    for (int j = 0; j < territoryList.size(); j++) {
      for (int k = 0; k < continentList.size(); k++) {
        if (territoryList.at(j)->getContinent() == continentList.at(k)) {
          continentList.erase(continentList.begin() + k);
        }
      }
    }

    // Remaining size of the continnent list is the bonus multiplier. Add bonus
    // to reinforcements
    reinforcements += continentList.size() * 3;

    // if lower than 3, assign 3 reinforcements
    if (reinforcements < 3) {
      reinforcements = 3;
    }

    players.at(i)->addReinforcements(reinforcements);

    cout << "Added " << reinforcements << " units to player " << i
         << " reinforcement pool" << std::endl;
  }
}

// Executes Issue Order state
void GameEngine::issueOrdersPhase() {
  // Global flag
  bool stillIssuingOrders = true;
  // Create a flag for each player to determine if they are done issuing orders.
  bool* playerStillIssuing = new bool[players.size()];

  for (int i = 0; i < players.size(); i++) {
    playerStillIssuing[i] = true;
  }

  while (stillIssuingOrders) {
    // Reset global flag
    stillIssuingOrders = false;

    for (int i = 0; i < players.size(); i++) {
      // Issue order and set player's flag. issueOrder() returns true if player
      // issues an order and flase if player signifies they are done.
      if (playerStillIssuing[i]) {
        playerStillIssuing[i] = players.at(i)->issueOrder();
        // Reset global flag if any player is still issuing orders
        stillIssuingOrders = true;
      }
    }
  }

  // Delete the flags
  delete[] playerStillIssuing;
}

// Execute Execute Orders state
void GameEngine::executeOrdersPhase() {
  // // Exec Execute Orders here
  for (int i = 0; i < players.size(); i++) {
    players.at(i)->getOrderList()->executeOrders();
  }
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

void handleEffect(const char effect[], Command &command, Observer *obs) {
  string s = effect;
  command.Attach(obs);
  command.saveEffect(s);
  cout << effect << std::endl;
}

void handleEffect(string &s, Command &command, Observer *obs) {
  command.Attach(obs);
  command.saveEffect(s);
  cout << s << std::endl;
}

void GameEngine::startupPhase() {
  // S_START state loading a map
  while (true) {
    printCommands();
    Command &result = commandProcessor->getCommand();
    if (result.param.size() == 0)
      handleEffect("Enter a file name in the format loadmap <filename>", result,
                   logObserver);
    else {
      string loadMapEffect = mapLoader->loadMap(result.param);
      if (loadMapEffect.size() == 0) {
        loadMapEffect = "\"" + result.param + "\" has been loaded";
        setState(GameEngineFSA::commandToStateMap.at("loadmap"));
        break;
      }
      handleEffect(loadMapEffect, result, logObserver);
    }
  }

  // S_MAP_LOADED state, load map or validate map
  // transition to S_MAP_VALIDATED validate is successful
  while (true) {
    printCommands();
    Command &result = commandProcessor->getCommand();

    // 2 possible commands: loadmap/validatemap
    if (result.command == "loadmap") {
      if (result.param.size() == 0)
        handleEffect("Enter a file name in the format loadmap <filename>",
                     result, logObserver);
      else {
        string loadMapEffect = mapLoader->loadMap(result.param);
        if (loadMapEffect.size() == 0) {
          loadMapEffect = "\"" + result.param + "\" has been loaded";
        }
        handleEffect(loadMapEffect, result, logObserver);
      }
    }

    else if (result.command == "validatemap") {
      string validateMapEffect;
      if (mapLoader->getMap()->validate()) {
        handleEffect(
            "The map passed all the tests and is a valid map to be used.",
            result, logObserver);
        setState(GameEngineFSA::commandToStateMap.at("validatemap"));
        break;
      } else {
        handleEffect(
            "The map has failed at least one test and is not a valid map. "
            "Try loading another map.",
            result, logObserver);
      }
    }
  }

  printCommands();

  // addPlayer implementation:
  bool done_adding_players = false;
  int nPlayers = 0;
  cout << "Enter 2-6 players in the format \"addplayer <playername>\"" << endl;
  cout << "When you have added all players, start game with \"gamestart\" "
          "command"
       << endl;

  while (!done_adding_players) {
    printCommands();
    Command &result = commandProcessor->getCommand();

    if (result.command == "addplayer") {
      if (result.param.size() == 0) {
        handleEffect(
            "Specify the player name in the format \"addplayer "
            "<playername>\"",
            result, logObserver);
        continue;
      }
      players.push_back(new Player(result.param));
      nPlayers++;
      cout << "Player named " << result.param << " has been added." << endl;
    } else if (result.command == "gamestart") {
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
      setState(GameEngineFSA::commandToStateMap.at("gamestart"));
  }

  // gamestart phase:

  mapLoader->getMap()->distributeTerritories(players);

  //  Randomly shuffle player vector to determine player order.
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(this->players.begin(), this->players.end(),
          std::default_random_engine(seed));

  // Each player gets 50 reincforcements and draws 2 cards
  for (int i = 0; i < players.size(); i++) {
    players.at(i)->addReinforcements(50);
    players.at(i)->getHand()->setDeck(deck);
    players.at(i)->getHand()->drawCard();
    players.at(i)->getHand()->drawCard();
    players.at(i)->getOrderList()->Attach(logObserver);
  }

  for (int i = 0; i < players.size(); i++) {
    cout << "Player " << i + 1 << ": " << *players.at(i) << endl;
  }
}

void GameEngine::mainGameLoop() {
  cout << " PLAYER SIZE: " << players.size() << endl;
  int turnCounter = 1;
  // Stop loop if there is only 1 player left
  while (players.size() > 1) {

    cout << "================ Beginning of turn " << turnCounter << " ================" << endl;
    
    cout << endl << "-------- Printing Deck -------- " << endl;
    cout << *deck << endl << endl;

    cout << endl << "-------- Printing Players -------- " << endl;
    for(Player* p : players){
        cout << *p << endl;
    }
    
    cout << endl << "-------- Reinforcement Phase --------"<< endl << endl;
    reinforcementPhase();
    cout << endl << "-------- Issue Orders Phase --------"<< endl << endl;
    issueOrdersPhase();
    cout << endl << "-------- Execute Orders Phase --------"<< endl << endl;
    executeOrdersPhase();
    // Check all players
    for (int i = 0; i < players.size(); i++) {
      // reset diplomatic allies
      players.at(i)->clearDiplomaticAllies();
      // check if player should draw a new card
      if (players.at(i)->getConcqueredFlag() == true) {
        //TODO John: make sure the card is removed from the deck as well.
        cout << players.at(i)->getName() << " is drawing a card.";
        players.at(i)->getHand()->drawCard();
        players.at(i)->setConcqueredFlag(false);
      }

    }
    // Removed Players with no Territories
    for (int i = 0; i < players.size(); i++) {
      // Remove players with less than 1 territory
      if (players.at(i)->getTerritories().size() < 1) {
        players.erase(players.begin() + i);
      }
    }
    
    cout << "================ End of turn " << turnCounter++ << " ================" << endl << endl;
  }
}

// overloaded stringToLog method
string GameEngine::stringToLog() {
  string s = "Game engine state change to: " + getLabel(this->state);
  return s;
}
