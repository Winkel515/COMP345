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

//command processor default constructor
CommandProcessor::CommandProcessor() {
};

//command processor constructor
CommandProcessor::CommandProcessor(set<string>* commands) {
  this->commands = commands;
};

//command processor copy constructor
CommandProcessor::CommandProcessor(const CommandProcessor& cp) {
  for (int i = 0; i < cp.commandList.size(); i++) {
    commandList.push_back(new Command(*cp.commandList.at(i)));
  }
};

//command processor destructor
CommandProcessor::~CommandProcessor() {
  for (int i = 0; i < commandList.size(); i++) delete commandList.at(i);
}

//command processor getCommand method
Command& CommandProcessor::getCommand() {
  vector<string> result = readCommand();
  return saveCommand(result);
}

//command procesor readcommand method
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

//overloaded stringTolog method
string CommandProcessor::stringToLog() {
  string s = "";
  if(this->commandList[(this->commandList).size()-1]->effect.size() == 0){
    s = this->commandList[(this->commandList).size()-1]->command 
    + " " + this->commandList[(this->commandList).size()-1]->param + " -> no effect";
  }
  else{
    s = this->commandList[(this->commandList).size()-1]->command 
    + " " + this->commandList[(this->commandList).size()-1]->param + " -> " 
    + this->commandList[(this->commandList).size()-1]->effect;
  }

  return s;
}

//command processor save command method
Command& CommandProcessor::saveCommand(vector<string>& result) {
  Command* newCommand = new Command(result);
  commandList.push_back(newCommand);
  cout << "CommandProcessor::saveCommand : command has been saved "
       << commandList.size() << endl;
  Notify(this); //newCommand
  return *newCommand;
}

//command processor validate method
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

//command default constructor
Command::Command() {}

//command copy constructor
Command::Command(const Command& c) {
  command = c.command;
  param = c.param;
  effect = c.effect;
}


//command constructor
Command::Command(vector<string>& result) {
  this->command = result.at(0);
  this->param = "";

  if (result.size() > 1) {
    this->param = result.at(1);
  }
}


//command saveeffect method
void Command::saveEffect(string& s) {
  effect = s;
  cout << "Effect: \"" << s << "\" has been saved\n";
  Notify(this);
}



//overloaded strinToLog method
string Command::stringToLog() {
  string s = "";
  
  if(this->effect.size() == 0){
    s = this->command + " " + this->param + " -> no effect"; //effect length = 0 say no effect
  }
  else{
    s = this->command + " " + this->param + " -> " + this->effect; //effect length = 0 say no effect
  }
  
  return s;
}

Command::~Command(){};

