#include "CommandProcessing.h"

#include <iostream>
#include <vector>

#include "GameEngine.h"
#include "Map.h"

using std::cin;
using std::cout;
using std::getline;

void CommandProcessor::getCommand() {
  string input = readCommand();
  saveCommand(input);
}

string CommandProcessor::readCommand() {
  string input = "";
  bool invalid = false;

  while (true) {
    if (invalid) {
      cout << "Try again.\n";
    }
    cout << "Please enter a command: ";
    getline(cin, input);
    if (validate(input))
      break;
    else
      invalid = true;
  };

  return input;
}

void CommandProcessor::saveCommand(string command) {
  Command* newCommand = new Command(command);
  commandList.push_back(newCommand);
  // create Command and add to commands vector
}

bool CommandProcessor::validate(string input) {
  // check gamestate and return if command is valid
}

Command::Command(string input) {
  // split string and store
  vector<string> store = splitString(input, " ");
  command = store.at(0);
  if (store.size() > 1) {
    param = store.at(1);
  }
}