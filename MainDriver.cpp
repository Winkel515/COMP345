#include <iostream>
#include <set>
#include <vector>

#include "CardsDriver.h"
#include "CommandProcessing.h"
#include "CommandProcessingDriver.h"
#include "GameEngineDriver.h"
#include "LoggingObserverDriver.h"
#include "MapDriver.h"
#include "OrdersDriver.h"
#include "PlayerDriver.h"

using std::cout;
using std::string;
using std::vector;
using std::stoi;

// Inits and Starts GameEngine given a command processor
void startGame(CommandProcessor* commandProcessor) {
  LogObserver logObs = LogObserver();
  commandProcessor->Attach(&logObs);
  GameEngine* gE = new GameEngine(commandProcessor);
  gE->Attach(&logObs);
  gE->start();
  delete gE;
}

// Helper to massage argv into filename
string getFileName(int argc, char* argv[]) {
  string filename = "";
  bool isFirst = true;
  for (int i = 2; i < argc; i++) {
    // Add space after the first concat
    if (!isFirst) {
      filename += " ";
    } else {
      isFirst = false;
    }
    string temp(argv[i]);
    filename += temp;
  }

  return filename;
}

void runA2Tests() {
  //cout << "====== Testing Command Processor ======\n";
  //testCommandProcessor();
  //cout << "====== Testing Logging observer ======\n";
  //testLoggingObserver();
  //cout << "====== Testing Startup Phase ======\n";
  //testStartupPhase();
  cout << "====== Testing Main Game Loop ======\n";
  testMainGameLoop();
  //cout << "====== Testing Order Execution ======\n";
  //testOrderExecution();

  cout << "End of Tests\n";
}

// Run old tests using this method
void runA1Tests() {
  cout << "====== Testing Map ======\n";
  testLoadMaps();
  cout << "====== Testing Players ======\n";
  testPlayers();
  cout << "====== Testing Cards ======\n";
  testCards();
  cout << "====== Testing Orders ======\n";
  testOrdersList();
  cout << "====== Testing Game Engine ======\n";
  testGameStates();
}

void showHelp(vector<string> supportedFlags) {
  cout << "Please launch the program with one of these arguments (i.e. "
          "out.exe -test):\n";
  for (int i = 0; i < supportedFlags.size(); i++) {
    if (i > 0) {
      cout << ", ";
    }
    cout << supportedFlags[i];
  }
  cout << "\n";
}

int main(int argc, char* argv[]) {
  CommandProcessor* commandProcessor;
  bool isDebug = false;  // Manually toggle
  vector<string> supportedFlags{
      "-console", "-file <filename>", "-test", "-help", "-a1", "-a2", "-tournament", "-M", "-P", "-G", "-D"};

  if (argc == 1) {
    // Run without any arguments
    isDebug = true;
    if (isDebug) {
      runA2Tests();
    } else {
      showHelp(supportedFlags);
    }
  } else if (argc >= 2) {
    // cast to string
    string flag(argv[1]);
    string flag2(argv[2]);
    string arg1(argv[3]);
    string flag3(argv[4]);
    string arg2(argv[5]);
    string flag4(argv[6]);
    string arg3(argv[7]);
    string flag5(argv[8]);
    string arg4(argv[9]);

    if (flag.compare("-help") == 0) {
      showHelp(supportedFlags);
    } else if (flag.compare("-test") == 0) {
      runA2Tests();  // run the latest tests
    } else if (flag.compare("-a2") == 0) {
      runA2Tests();  // run the a2 tests
    } else if (flag.compare("-a1") == 0) {
      runA1Tests();  // run the old tests
    } else if (flag.compare("-console") == 0) {
      // Run using console input
      commandProcessor = new CommandProcessor();
      startGame(commandProcessor);
    } else if (flag.compare("-tournament") == 0 && flag2.compare("-M") == 0 && flag3.compare("-P") == 0 && flag4.compare("-G") == 0 && flag5.compare("-D") == 0) {
      // Run using tournament mode
      int listOfMapFiles = std::stoi(arg1);
      int listOfPlayersStrategies = std::stoi(arg2);
      int numberOfGames = std::stoi(arg3);
      int numberOfTurns = std::stoi(arg4);
    } else if (flag.compare("-file") == 0) {
      // Massage to get filename
      std::string filename;
      if (argc > 2) {
        filename = getFileName(argc, argv);
      } else {
        // by default
        cout << "Using default file testcommands.txt (provide a filename to "
                "override)."
             << endl;
        filename = "testcommands.txt";
      }

      // Run using file input
      commandProcessor = new FileCommandProcessorAdapter(filename);
      startGame(commandProcessor);

    } else {
      cout << "Unsupported flag. Please run using supported flag.\n";
    }
  } else {
    // Show help by default
    showHelp(supportedFlags);
    return 0;
  }
}