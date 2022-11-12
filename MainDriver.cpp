#include <iostream>
#include <vector>

#include "CardsDriver.h"
#include "GameEngineDriver.h"
#include "LoggingObserverDriver.h"
#include "MapDriver.h"
#include "OrdersDriver.h"
#include "PlayerDriver.h"

using std::cout;
using std::string;
using std::vector;

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

int main(int argc, char *argv[]) {
  bool isDebug = true;  // Manually toggle
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
    } else if (flag.compare("-test")) {
      oldTests();  // TODO temporarily
    } else if (flag.compare("-oldtests") == 0) {
      oldTests();
    } else {
      cout << "Unsupported flag. Please run using supported flag.\n";
    }
  } else {
    showHelp(supportedFlags);
    return 0;
  }
}