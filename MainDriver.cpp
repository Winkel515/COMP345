#include <iostream>
#include <set>
#include <vector>

#include "CardsDriver.h"
#include "CommandProcessing.h"
#include "GameEngineDriver.h"
#include "LoggingObserverDriver.h"
#include "MapDriver.h"
#include "OrdersDriver.h"
#include "PlayerDriver.h"

using std::cout;
using std::string;
using std::vector;

string getFileName(int argc, char *argv[]) {
  string filename = "";
  bool isFirst = true;
  for(int i = 2; i < argc; i++) {
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

void oldTests() {
  cout << "====== Testing Map ======\n";
  testLoadMaps();
  cout << "====== Testing Players ======\n";
  testPlayers();
  cout << "====== Testing Cards ======\n";
  testCards();
  cout << "====== Testing Orders ======\n";
  testOrdersList();
  cout << "====== Testing Game Engine ======\n";
  // testGameStates();
  cout << "====== Testing Logging observer ======\n";
  testLoggingObserver();
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
  vector<string> supportedFlags{"-help", "-oldtests"};

  if (argc == 1) {
    // Run without any arguments
    if (isDebug) {
      oldTests();  // TODO
    } else {
      showHelp(supportedFlags);
    }
  } else if (argc >= 2) {
    // cast to string
    string flag(argv[1]);

    if (flag.compare("-help") == 0) {
      showHelp(supportedFlags);
    } else if (flag.compare("-test") == 0) {
      oldTests();  // TODO temporarily
    } else if (flag.compare("-oldtests") == 0) {
      oldTests();
    } else if (flag.compare("-console") == 0) {
      oldTests();  // TODO
    } else if (flag.compare("-file") == 0) {
      std::set<string> validCommands = {"test1", "test2", "loadmap"};
      std::string filename;

      if (argc > 2) {
        filename = getFileName(argc, argv);
      } else {
        // by default
        filename = "commands.txt";
      }

      commandProcessor =
          new FileCommandProcessorAdapter(filename);
      commandProcessor->initCommandsPtr(&validCommands);
      commandProcessor->getCommand();
      delete commandProcessor;

    } else {
      cout << "Unsupported flag. Please run using supported flag.\n";
    }
  } else {
    showHelp(supportedFlags);
    return 0;
  }

  // if (commandProcessor != nullptr) {
  //   delete commandProcessor;
  // }
}