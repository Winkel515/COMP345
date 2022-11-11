#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <string>
#include <vector>

#include "GameEngine.h"
#include "LoggingObserver.h"

using std::set;
using std::string;
using std::vector;

class Command : public Subject, public ILoggable {
 public:
  string command;
  string param;
  Command();
  Command(vector<string> &);
  Command(const Command &);
  ~Command();
  void saveEffect(string);
  void callNotify();
  string stringToLog();
};

class CommandProcessor : public Subject, public ILoggable {
  vector<Command *> commandList;
  set<string> *commands;

  vector<string> readCommand();
  
  bool validate(vector<string> &);

 public:
 void saveCommand(vector<string> &);
  vector<string> getCommand();
  CommandProcessor();
  CommandProcessor(set<string> *);
  CommandProcessor(const CommandProcessor &);
  ~CommandProcessor();
  string stringToLog();
};

#endif