#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <fstream>
#include <string>
#include <vector>

#include "GameEngine.h"
#include "LoggingObserver.h"

using std::ifstream;
using std::set;
using std::string;
using std::vector;

class Command : public Subject, public ILoggable {
 public:
  string command;
  string param;
  string effect;
  Command();
  Command(vector<string> &);
  Command(const Command &);
  ~Command();
  void saveEffect(string &);
  void callNotify();
  string stringToLog();
};

class CommandProcessor : public Subject, public ILoggable {
  virtual Command& readCommand();

 protected:
  vector<Command *> commandList;
  set<string> *validCommands;
  Command &saveCommand(vector<string> &);
  bool validate(vector<string> &);

 public:
  Command &getCommand();
  CommandProcessor();
  CommandProcessor(set<string> *);
  CommandProcessor(const CommandProcessor &);
  ~CommandProcessor();
  string stringToLog();
  void initCommandsPtr(set<string> *);
};

class FileCommandProcessorAdapter : public CommandProcessor {
  // CommandProcessor *adaptee; // No need, already has super class thanks to
  // protected
  ifstream file;
  Command& readCommand();

 public:
  // FileCommandProcessorAdapter();
  FileCommandProcessorAdapter(string);
  FileCommandProcessorAdapter(set<string> *, string);
  ~FileCommandProcessorAdapter();
};

#endif