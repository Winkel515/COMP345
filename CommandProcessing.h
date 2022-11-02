#include <string>
#include <vector>

#include "LoggingObserver.h"
class GameEngine;

using std::string;
using std::vector;

class Command {
  string command;
  string param;

 public:
  Command(string s);
  ~Command();
};

class CommandProcessor : public Subject, public ILoggable {
  vector<Command*> commandList;

  string readCommand();
  void saveCommand(string);
  bool validate(string);

 public:
  void getCommand();
  CommandProcessor();
  ~CommandProcessor();
  string stringToLog();
};
