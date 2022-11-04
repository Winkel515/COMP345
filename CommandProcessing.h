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
  string command;
  string param;

 public:
  Command(vector<string> &);
  Command(const Command &);
  ~Command();
  void saveEffect(string);
  string stringToLog();
};

class CommandProcessor {
  vector<Command *> commandList;
  set<string> *commands;

  vector<string> readCommand();
  void saveCommand(vector<string> &);
  bool validate(vector<string> &);

 public:
  vector<string> getCommand();
  CommandProcessor(set<string> *);
  CommandProcessor(const CommandProcessor &);
  ~CommandProcessor();
  string stringToLog();
};

#endif