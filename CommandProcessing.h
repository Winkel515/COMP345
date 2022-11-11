#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <string>
#include <vector>

#include "GameEngine.h"
#include "LoggingObserver.h"

using std::set;
using std::string;
using std::vector;

class Command {
 public:
  string command;
  string param;
  string effect;
  Command(vector<string> &);
  Command(const Command &);
  ~Command();
  void saveEffect(string &);
  string stringToLog();
};

class CommandProcessor {
  vector<Command *> commandList;
  set<string> *commands;

  vector<string> readCommand();
  Command &saveCommand(vector<string> &);
  bool validate(vector<string> &);

 public:
  Command &getCommand();
  CommandProcessor(set<string> *);
  CommandProcessor(const CommandProcessor &);
  ~CommandProcessor();
  string stringToLog();
};

#endif