#include "CommandProcessing.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "GameEngine.h"

using std::cin;
using std::cout;
using std::getline;
using std::ofstream;

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

string CommandProcessor::stringToLog() {
  ofstream output;
  output.open("gamelog.txt", std::ios_base::app);
  output << "print to gamelog" << endl;
  output << "In command processor" << endl;
  output.close();
  return "string";
}

void CommandProcessor::saveCommand(string command) {
  Command* newCommand = new Command(command);
  commandList.push_back(newCommand);
  Notify(this);
  // create Command and add to commands vector
}

bool CommandProcessor::validate(string input) {
  // check gamestate and return if command is valid
  return false;  // just to make compiler happy
}

Command::Command(string input) {
  // split string and store
  vector<string> store = splitString(input, " ");
  command = store.at(0);
  if (store.size() > 1) {
    param = store.at(1);
  }
}