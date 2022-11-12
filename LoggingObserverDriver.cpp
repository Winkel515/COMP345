#include <typeinfo>
#include <fstream>
#include <iostream>
#include "LoggingObserverDriver.h"
#include "LoggingObserver.h"
#include "GameEngine.h"
#include "Orders.h"
#include "CommandProcessing.h"

using std::cout, std::endl;
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
    //LogObserver* gameEngineView = new LogObserver(testGameEngine);
    cout << "testGameEngine is of type: " << typeid(testGameEngine).name() << " and inherits from "
     << typeid(dynamic_cast<Subject*>(testGameEngine)).name() << " and " 
     << typeid(dynamic_cast<ILoggable*>(testGameEngine)).name() << endl;

    Order* testOrder = new Order();
    //LogObserver* orderView = new LogObserver(testOrder);
    cout << "testOrder is of type: " << typeid(testOrder).name() << " and inherits from "
     << typeid(dynamic_cast<Subject*>(testOrder)).name() << " and " 
     << typeid(dynamic_cast<ILoggable*>(testOrder)).name() << endl;

    OrdersList* testOrdersList = new OrdersList();
    //LogObserver* ordersListView = new LogObserver(testOrdersList);
    cout << "testOrdersList is of type: " << typeid(testOrdersList).name() << " and inherits from "
     << typeid(dynamic_cast<Subject*>(testOrdersList)).name() << " and " 
     << typeid(dynamic_cast<ILoggable*>(testOrdersList)).name() << endl;

    vector<string> commandsVec;
    commandsVec.push_back("loadmap");
    commandsVec.push_back("3D.map");
    Command* testCommands = new Command(commandsVec);
    //LogObserver* commandsView = new LogObserver(testCommands);
    cout << "testCommands is of type: " << typeid(testCommands).name() << " and inherits from "
     << typeid(dynamic_cast<Subject*>(testCommands)).name() << " and " 
     << typeid(dynamic_cast<ILoggable*>(testCommands)).name() << endl;

    set<string> commandsSet;
    commandsSet.insert("loadmap");
    CommandProcessor* testCommandProcessor = new CommandProcessor(&commandsSet);
    //LogObserver* commandProcessorView = new LogObserver(testCommandProcessor);
    cout << "testCommandProcessor is of type: " << typeid(testCommandProcessor).name() << " and inherits from "
     << typeid(dynamic_cast<Subject*>(testCommandProcessor)).name() << " and " 
     << typeid(dynamic_cast<ILoggable*>(testCommandProcessor)).name() << endl;
    
    testGameEngine->setState(GameState::S_MAP_LOADED);
    testOrder->execute();
    testOrdersList->add(testOrder);
    testCommands->saveEffect("Command Failed");
    testCommandProcessor->saveCommand(commandsVec);

    output.open("gamelog.txt", std::ios_base::app);
    output << "================================\n\n" << endl;
    output << "the file gets correctly written into when commands are entered on the console \n\n" << endl;
    output.close();

    GameEngine* testGameEngine2 = new GameEngine;
    //LogObserver* gameEngineView2 = new LogObserver(testGameEngine2);
    testGameEngine2->start();



    delete testGameEngine;
    delete testGameEngine2;
    delete testOrder;
    //delete testOrdersList;
    delete testCommands;
    delete testCommandProcessor;
    //delete commandProcessorView;
    cout << "end" << endl;
}