#include "TournamentDriver.h"
#include "GameEngine.h"
#include <iostream>
using std::cout;
using std::endl;

void testTournament(){

    cout << "- Testing testTournament: Running Game States\n";
    GameEngine* runningGameEngine = new GameEngine;
    runningGameEngine->start();
    std::cout << "Game engine started " << *runningGameEngine << endl;
    while (runningGameEngine->getState() != GameState::S_END) {
        std::cout << *runningGameEngine;
        runningGameEngine->promptCommand();
    }

    // delete fileGameEngine;
    delete runningGameEngine;
}