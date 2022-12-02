#include <iostream>
#include "PlayerStrategies.h"
#include "Player.h"
using std::cout, std::endl;

void testPlayerStrategies(){

    Player* p1 = new Player("Bob", new CheaterPlayerStrategy(p1));
    

    cout << "bla from player strategy " << *p1 <<endl;


}