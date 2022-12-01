#include "PlayerStrategies.h"
#include <vector>
#include "Map.h"
#include "Player.h"

using std::vector;

//TODO John: Implement all Parametrized constructors

PlayerStrategy::PlayerStrategy(Player* p) {
    this->p = p;
}


// ============ Human Player ==============

bool HumanPlayerStrategy::issueOrder(){

    return true;
}

vector<Territory*> HumanPlayerStrategy::toAttack(){
    vector<Territory*> terri;
    return terri;
}

vector<Territory*> HumanPlayerStrategy::toDefend(){
    vector<Territory*> terri;
    return terri;
}

// ============ Cheater Player ==============

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) : PlayerStrategy(p) {
}

bool CheaterPlayerStrategy::issueOrder(){

    //TODO: Automatically conquer all adjacent territories
    vector<Territory*> toConquer =  p->getAdjacentTerritories();
    for (Territory* t : toConquer){
        //TODO: Remove territory from opponents' territory vector
        Player* oldOwner = t->getOwner();

        //TODO: Set new Owner
        t->setOwner(p);
    }

    //No more orders needed
    return false;
}


vector<Territory*> CheaterPlayerStrategy::toAttack(){
    vector<Territory*> terri;
    return terri;
}

vector<Territory*> CheaterPlayerStrategy::toDefend(){
    vector<Territory*> terri;
    return terri;
}

// ============ Aggressive Player ==============

bool AggressivePlayerStrategy::issueOrder(){

    return true;
}

vector<Territory*> AggressivePlayerStrategy::toAttack(){
    vector<Territory*> terri;
    return terri;
}

vector<Territory*> AggressivePlayerStrategy::toDefend(){
    vector<Territory*> terri;
    return terri;
}

// ============ Benevolent Player ==============

bool BenevolentPlayerStrategy::issueOrder(){

    return true;
}

vector<Territory*> BenevolentPlayerStrategy::toAttack(){
    vector<Territory*> terri;
    return terri;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend(){
    vector<Territory*> terri;
    return terri;
}

// ============ Neutral Player ==============

bool NeutralPlayerStrategy::issueOrder(){

    return true;
}

vector<Territory*> NeutralPlayerStrategy::toAttack(){
    vector<Territory*> terri;
    return terri;
}

vector<Territory*> NeutralPlayerStrategy::toDefend(){
    vector<Territory*> terri;
    return terri;
}