#include <iostream>
#include <vector>

#include "CardsDriver.h"
#include "GameEngineDriver.h"
#include "MapDriver.h"
#include "OrdersDriver.h"
#include "PlayerDriver.h"
#include "LoggingObserverDriver.h"

using std::cout;
using std::string;
using std::vector;

int main(int argc, char *argv[]) {
  if (argc >= 2) {
    // cast to string
    string flag(argv[1]);
    vector<string> supportedFlags{"-help", "-oldtests"};

    if (flag.compare("-help") == 0) {
      cout << "Please launch the program with one of these arguments (i.e. "
              "out.exe -test):\n";
      for (int i = 0; i < supportedFlags.size(); i++) {
        if (i > 0) {
          cout << ", ";
        }
        cout << supportedFlags[i];
      }
      cout << "\n";
    } else if (flag.compare("-oldtests") == 0) {
      cout << "====== Testing Map ======\n";
      testLoadMaps();
      cout << "====== Testing Players ======\n";
      testPlayers();
      cout << "====== Testing Cards ======\n";
      testCards();
      cout << "====== Testing Orders ======\n";
      testOrdersList();
      cout << "====== Testing Game Engine ======\n";
      //testGameStates();
      cout << "====== Testing Logging observer ======\n";
      testLoggingObserver();
    } else {
      cout << "Unsupported flag. Please run using supported flag.\n";
    }
  } else {
    cout << "Please use an argument (i.e a.exe -test).\n";
  }
  return 0;
}