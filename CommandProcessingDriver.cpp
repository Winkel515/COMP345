#include "CommandProcessingDriver.h"

#include <iostream>
#include <set>

#include "CommandProcessing.h"
#include "GameEngine.h"

using std::cout;
using std::endl;
using std::set;
using std::string;

// If we want to test using a real game instance use
// testStartGame(CommandProcessor)
void testStartGame(CommandProcessor* commandProcessor) {
  LogObserver logObs = LogObserver();
  commandProcessor->Attach(&logObs);
  GameEngine* gE = new GameEngine(commandProcessor);
  gE->Attach(&logObs);
  gE->start();
}

// Demonstrates command can be read from console or file, and that invalid
// commands are rejected.
void testCommandProcessor() {
  cout << "Only the command \"valid\" will be accepted in this test" << endl;
  set<string> validCommands;
  validCommands.insert("valid");

  cout << "Using Console command processor" << endl;
  CommandProcessor cp = CommandProcessor(&validCommands);
  cp.getCommand();

  cout << "Using File command processor" << endl;
  string filename = "testcommands.txt";
  // Polymorphism
  CommandProcessor* fp =
      new FileCommandProcessorAdapter(&validCommands, filename);
  fp->getCommand();

  delete fp;
}