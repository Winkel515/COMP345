#include "CommandProcessing.h"


#include <iostream>
#include <string>
#include <vector>

#include "GameEngine.h"

using std::cin;
using std::cout;
using std::getline;
using std::set;
using std::string;

CommandProcessor::CommandProcessor() {
};

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
string CommandProcessor::stringToLog() {
  string s = "CommandProcessor class \ncommand " + 
  this->commandList[(this->commandList).size()-1]->command + "\nparam " + 
  this->commandList[(this->commandList).size()-1]->param + "\n";
  //string s2 = this->commandList[(this->commandList).size()-1]->command + "\nparam ";
  //string s3 = this->commandList[(this->commandList).size()-1]->param + "\n";
  /*for (int i = 0; i < (this->commandList).size(); i++) {
    s += "command " + i;
    s += " " + this->commandList[i]->command + "\n";
    s += "param " + i;
    s += " " + this->commandList[i]->param + "\n";
  }*/
  //cout << endl << s1 << endl;
  return s;
}

void CommandProcessor::saveCommand(vector<string>& result) {
  Command* newCommand = new Command(result);
  //LogObserver* commandView = new LogObserver(newCommand);
  commandList.push_back(newCommand);
  cout << "CommandProcessor::saveCommand : command has been saved "
       << commandList.size() << endl;
  Notify(newCommand); //newCommand
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

Command::Command() {

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
string Command::stringToLog() {
  string s = "command class\ncommand " + this->command + " param " + this->param;
  return s;
}

Command::~Command(){}; //TODO: check if it is okay