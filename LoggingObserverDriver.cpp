#include "LoggingObserverDriver.h"

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <vector>

#include "CommandProcessing.h"
#include "GameEngine.h"
#include "LoggingObserver.h"
#include "Orders.h"

using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

void testLoggingObserver() {
  ofstream output;
  output.open("gamelog.txt", std::ios_base::app);
  output << "\n\n================================" << endl;
  output << "Starting Logging Observer tests" << endl;
  output << "================================\n\n" << endl;
  output << "Notify(Subject) trigers an entry in the log file \n\n" << endl;
  output.close();

  cout << "================================" << endl;
  cout << "In test logging observer" << endl;

  GameEngine* testGameEngine = new GameEngine;
  // LogObserver* gameEngineView = new LogObserver(testGameEngine);
  cout << "testGameEngine is of type: " << typeid(testGameEngine).name()
       << " and inherits from "
       << typeid(dynamic_cast<Subject*>(testGameEngine)).name() << " and "
       << typeid(dynamic_cast<ILoggable*>(testGameEngine)).name() << endl;

  Player* p1 = new Player("player 1");
  Territory* terr1 = new Territory("player1Territory", "fakeContinent");
  terr1->setOwner(p1);
  Order* testOrder = new Deploy(terr1, p1, 10);
  LogObserver logObs = LogObserver();
  testOrder->Attach(&logObs);
  // LogObserver* orderView = new LogObserver(testOrder);
  cout << "testOrder is of type: " << typeid(testOrder).name()
       << " and inherits from "
       << typeid(dynamic_cast<Subject*>(testOrder)).name() << " and "
       << typeid(dynamic_cast<ILoggable*>(testOrder)).name() << endl;
  // prints types of orderslist
  OrdersList* testOrdersList = new OrdersList();
  testOrdersList->Attach(&logObs);
  cout << "testOrdersList is of type: " << typeid(testOrdersList).name()
       << " and inherits from "
       << typeid(dynamic_cast<Subject*>(testOrdersList)).name() << " and "
       << typeid(dynamic_cast<ILoggable*>(testOrdersList)).name() << endl;

  // prints types of command
  vector<string> commandsVec;
  commandsVec.push_back("loadmap");
  commandsVec.push_back("3D.map");
  Command* testCommands = new Command(commandsVec);
  testCommands->Attach(&logObs);
  cout << "testCommands is of type: " << typeid(testCommands).name()
       << " and inherits from "
       << typeid(dynamic_cast<Subject*>(testCommands)).name() << " and "
       << typeid(dynamic_cast<ILoggable*>(testCommands)).name() << endl;

  // prints types of commandprocessor
  set<string> commandsSet;
  commandsSet.insert("loadmap");
  CommandProcessor* testCommandProcessor = new CommandProcessor(&commandsSet);
  testCommandProcessor->Attach(&logObs);
  cout << "testCommandProcessor is of type: "
       << typeid(testCommandProcessor).name() << " and inherits from "
       << typeid(dynamic_cast<Subject*>(testCommandProcessor)).name() << " and "
       << typeid(dynamic_cast<ILoggable*>(testCommandProcessor)).name() << endl;

  // Testing Notify from GameEngine, Order and Commands
  testGameEngine->setState(GameState::S_MAP_LOADED);
  // TODO
  // testOrder->execute();
  // testOrdersList->add(testOrder);
  string effectString = "Command Failed";
  testCommands->saveEffect(effectString);

  // Testing Notify from saveCommand()
  testCommandProcessor->setNextInput("loadmap");
  testCommandProcessor->getCommand();

  output.open("gamelog.txt", std::ios_base::app);
  output << "================================\n\n" << endl;
  output << "the file gets correctly written into when commands are entered on "
            "the console \n\n"
         << endl;
  output.close();

  // Testing Notify when GameEngine runs from console inputs
  GameEngine* testGameEngine2 = new GameEngine;
  testGameEngine2->Attach(&logObs);
  testGameEngine2->start();

  delete testGameEngine;
  delete testGameEngine2;
  delete testOrder;
  // delete testOrdersList;
  delete testCommands;
  delete testCommandProcessor;
  delete p1;
  delete terr1;
  // delete commandProcessorView;
  cout << "end" << endl;
}