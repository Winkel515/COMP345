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

CommandProcessor::~CommandProcessor() {
  for (int i = 0; i < commandList.size(); i++) delete commandList.at(i);
}

Command& CommandProcessor::getCommand() {
  vector<string> result = readCommand();
  return saveCommand(result);
}

vector<string> CommandProcessor::readCommand() {
  string input = "";
  vector<string> result;

  while (true) {
    cout << "Please enter a command: ";
    getline(cin, input);
    result = splitString(input, " ");
    if (validate(result)) break;
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

Command& CommandProcessor::saveCommand(vector<string>& result) {
  Command* newCommand = new Command(result);
  commandList.push_back(newCommand);
  cout << "CommandProcessor::saveCommand : command has been saved "
       << commandList.size() << endl;
  return *newCommand;
  // Notify(this);
  // create Command and add to commands vector
}

bool CommandProcessor::validate(vector<string>& result) {
  // check gamestate and return if command is valid
  string command = result.at(0);
  // Checks if valid command
  if (commands->find(command) == commands->end()) {
    string invalidEffect = "Invalid Command.";
    saveCommand(result).saveEffect(invalidEffect);
    cout << invalidEffect << std::endl;
    printCommands(*commands);
    return false;
  }

  return true;
}

Command::Command(const Command& c) {
  command = c.command;
  param = c.param;
  effect = c.effect;
}

Command::Command(vector<string>& result) {
  command = result.at(0);
  param = "";
  effect = "";
  if (result.size() > 1) {
    param = result.at(1);
  }
}

Command::~Command() {}

void Command::saveEffect(string& s) {
  effect = s;
  cout << "Effect: \"" << s << "\" has been saved\n";
  //  Notify(this);
}