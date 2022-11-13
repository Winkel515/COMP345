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

CommandProcessor::CommandProcessor(){};

CommandProcessor::CommandProcessor(set<string>* commands) {
  this->validCommands = commands;
};

CommandProcessor::CommandProcessor(const CommandProcessor& cp) {
  for (int i = 0; i < cp.commandList.size(); i++) {
    commandList.push_back(new Command(*cp.commandList.at(i)));
  }
};

CommandProcessor::~CommandProcessor() {
  for (int i = 0; i < commandList.size(); i++) delete commandList.at(i);
}

void CommandProcessor::setNextInput(string input) {
  nextInput = input;
}

Command& CommandProcessor::getCommand() { 
  // Run normally if nextInput is empty
  if(nextInput.empty()) {
    return readCommand();
  } else {
    // Run manually if nextInput was set manually (for testing)
    string input = nextInput;
    nextInput = "";
    vector<string> inputs = splitString(input, " ");
    if (validate(inputs)) {
      return saveCommand(inputs);
    } else {
      cout << "When using nextInput, the input must be valid.\nQuitting.\n";
      std::exit(0);
      Command * doesntReach_keepCompilerHappy = new Command(inputs); // doesnt reach
      return *doesntReach_keepCompilerHappy; // doesnt reach
    }
  }
}

Command& CommandProcessor::readCommand() {
  string input = "";
  vector<string> inputs;

  while (true) {
    cout << "Please enter a command: ";
    getline(cin, input);
    inputs = splitString(input, " ");
    if (validate(inputs)) {
      return saveCommand(inputs);
    }
  }
}

// overloaded stringTolog method
string CommandProcessor::stringToLog() {
  string s = "CommandProcessor class \ncommand " +
             this->commandList[(this->commandList).size() - 1]->command +
             "\nparam " +
             this->commandList[(this->commandList).size() - 1]->param + "\n";
  // string s2 = this->commandList[(this->commandList).size()-1]->command +
  // "\nparam "; string s3 =
  // this->commandList[(this->commandList).size()-1]->param + "\n";
  /*for (int i = 0; i < (this->commandList).size(); i++) {
    s += "command " + i;
    s += " " + this->commandList[i]->command + "\n";
    s += "param " + i;
    s += " " + this->commandList[i]->param + "\n";
  }*/
  // cout << endl << s1 << endl;
  return s;
}

Command& CommandProcessor::saveCommand(vector<string>& result) {
  Command* newCommand = new Command(result);
  // LogObserver* commandView = new LogObserver(newCommand);
  commandList.push_back(newCommand);
  cout << "CommandProcessor::saveCommand : command has been saved "
       << commandList.size() << endl;
  Notify(newCommand);
  return *newCommand;
}

void Command::callNotify() { Notify(this); }

bool CommandProcessor::validate(vector<string>& result) {
  // check gamestate and return if command is valid
  string command = result.at(0);
  // Checks if valid command
  if (validCommands->find(command) == validCommands->end()) {
    string invalidEffect = "Invalid Command.";
    saveCommand(result).saveEffect(invalidEffect);
    cout << invalidEffect << std::endl;
    printCommands(*validCommands);
    return false;
  }

  return true;
}

void CommandProcessor::initValidCommandsPtr(set<string>* commands) {
  this->validCommands = commands;
}

Command::Command() {}

Command::Command(const Command& c) {
  command = c.command;
  param = c.param;
  effect = c.effect;
}

Command::Command(vector<string>& result) {
  this->command = result.at(0);
  this->param = "";

  if (result.size() > 1) {
    this->param = result.at(1);
  }
}

void Command::saveEffect(string& s) {
  effect = s;
  cout << "Effect: \"" << s << "\" has been saved\n";
  //  Notify(this);
}

// overloaded strinToLog method
string Command::stringToLog() {
  string s =
      "command class\ncommand " + this->command + " param " + this->param;
  return s;
}

Command::~Command(){};

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string filename) {
  file.open(filename);

  if (!file.good()) {
    cout << "Commands file \"" << filename << "\" does not exist." << endl;
    std::exit(0);
  }
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(set<string>* commands,
                                                         string filename)
    : FileCommandProcessorAdapter(filename) {
  this->validCommands = commands;
}

// Close the file once done
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() { file.close(); }

Command& FileCommandProcessorAdapter::readCommand() {
  string input = "";
  Command response;
  vector<string> inputs = {""};

  // Read line until get a valid command
  while (true) {
    if (!file.eof()) {
      getline(file, input);
      cout << "Read \"" + input + "\" from file." << endl;
      
      // Protect from seg fault
      if (input.length() > 0) {
        // Convert into vector
        inputs = splitString(input, " ");
      }
      // Validate
      if (validate(inputs)) {
        return saveCommand(inputs);
      };
    } else {
      // Quits app once EOF
      cout << "Reached EOF." << endl;
      cout << "Quitting application." << endl;
      std::exit(0);
    }
  }
}
