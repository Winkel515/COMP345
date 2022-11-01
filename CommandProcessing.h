#include <string>
#include <vector>

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

class CommandProcessor {
  vector<Command*> commandList;

  string readCommand();
  void saveCommand(string);
  bool validate(string);

 public:
  void getCommand();
  CommandProcessor();
  ~CommandProcessor();
};
