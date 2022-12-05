#include <iostream>
#include "PlayerStrategies.h"
#include "Player.h"
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "LoggingObserver.h"
using std::cout;
using std::endl;

void testPlayerStrategies(){
    
    GameEngine* testEngine = new GameEngine();
    CommandProcessor* cp = testEngine->commandProcessor;
    
    cp->setNextInput("tournament -M 3D.map -P human neutral -G 3 -D 30");
    
    testEngine->startupPhase();

    delete testEngine;
}