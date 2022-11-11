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

//overloaded stringTolog method
void CommandProcessor::stringToLog() {
  ofstream output;
  output.open("gamelog.txt", std::ios_base::app);
  output << "print to gamelog" << endl;
  for (int i = 0; i < (this->commandList).size(); i++) {
    output << "command " << i << " " << this->commandList[i]->command << endl;
    output << "param " << i << " " << this->commandList[i]->param << endl;
  }
  output << "In command processor" << endl;
  output.close();
  
}

void CommandProcessor::saveCommand(vector<string>& result) {
  Command* newCommand = new Command(result);
  LogObserver* commandView = new LogObserver(newCommand);
  commandList.push_back(newCommand);
  cout << "CommandProcessor::saveCommand : command has been saved "
       << commandList.size() << endl;
  Notify(this);
}

void Command::callNotify() { Notify(this); }

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
  this->command = c.command;
  this->param = c.param;
}

Command::Command(vector<string>& result) {
  this->command = result.at(0);
  this->param = "";
  if (result.size() > 1) {
    this->param = result.at(1);
  }
}


void Command::saveEffect(string s) { Notify(this); }

//overloaded strinToLog method
void Command::stringToLog() {
  ofstream output;
  output.open("gamelog.txt", std::ios_base::app);
  output << "print to gamelog" << endl;
  output << "command " << this->command << " param " << this->param << endl;
  output << "In command " << endl;
  output.close();
}

Command::~Command(){}; //TODO: check if it is okay