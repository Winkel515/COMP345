#include "CommandProcessing.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "GameEngine.h"

using std::cin;
using std::cout;
using std::getline;
using std::ofstream;
using std::set;
using std::string;

CommandProcessor::CommandProcessor(set<string>* commands) {
  this->commands = commands;
};

CommandProcessor::CommandProcessor(const CommandProcessor& cp) {
  for (int i = 0; i < cp.commandList.size(); i++) {
    commandList.push_back(new Command(*cp.commandList.at(i)));
  }
};

vector<string> CommandProcessor::getCommand() {
  vector<string> result = readCommand();
  saveCommand(result);
  return result;
}

vector<string> CommandProcessor::readCommand() {
  string input = "";
  bool invalid = false;
  vector<string> result;

  while (true) {
    if (invalid) {
      cout << "Try again.\n";
    }
    cout << "Please enter a command: ";
    getline(cin, input);
    result = splitString(input, " ");
    if (validate(result))
      break;
    else
      invalid = true;
  };

  return result;
}

string CommandProcessor::stringToLog() {
  ofstream output;
  output.open("gamelog.txt", std::ios_base::app);
  output << "print to gamelog" << endl;
  output << "In command processor" << endl;
  output.close();
  return "string";
}

void CommandProcessor::saveCommand(vector<string>& result) {
  Command* newCommand = new Command(result);
  commandList.push_back(newCommand);
  cout << "CommandProcessor::saveCommand : command has been saved "
       << commandList.size() << endl;
  // Notify(this);
  //   create Command and add to commands vector
}

bool CommandProcessor::validate(vector<string>& result) {
  // check gamestate and return if command is valid
  string command = result.at(0);
  // Checks if valid command
  if (commands->find(command) == commands->end()) {
    cout << "Invalid Command.\n";
    return false;
  }

  return true;
}

Command::Command(const Command& c) {
  command = c.command;
  param = c.param;
}

Command::Command(vector<string>& result) {
  command = result.at(0);
  param = "";
  if (result.size() > 1) {
    param = result.at(1);
  }
}

void Command::saveEffect(string s) {
  //  Notify(this);
}

string Command::stringToLog() {
  ofstream output;
  output.open("gamelog.txt", std::ios_base::app);
  output << "print to gamelog" << endl;
  output << "In command " << endl;
  output.close();
  return "string";
}