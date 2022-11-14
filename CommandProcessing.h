#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include "GameEngine.h"
#include "LoggingObserver.h"

using std::ifstream;
using std::set;
using std::string;
using std::vector;
using std::queue;

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
  string stringToLog();
};

class CommandProcessor : public Subject, public ILoggable {
  virtual Command& readCommand();
  Command& readCommand(bool);

 protected:
  vector<Command *> commandList;
  set<string> *validCommands;
  Command &saveCommand(vector<string> &);
  Command &getValidatedAndSavedCommand(string);
  bool validate(vector<string> &);
  queue<string> nextInput;

 public:
  Command &getCommand();
  Command &getCommand(bool);
  void setNextInput(string); // Careful: Only implemented in CommandProcessor, Adapter doesnt use this.
  CommandProcessor();
  CommandProcessor(set<string> *);
  CommandProcessor(const CommandProcessor &);
  virtual ~CommandProcessor();
  string stringToLog();
  void initValidCommandsPtr(set<string> *);
  friend class Command;
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