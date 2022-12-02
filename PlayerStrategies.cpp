#include "PlayerStrategies.h"
#include <vector>
#include <algorithm>
#include "Map.h"
#include "Player.h"

using std::vector;

PlayerStrategy::PlayerStrategy(Player* p){
    this->p = p;
}

bool HumanPlayerStrategy::issueOrder(){

    return true;
}

vector<Territory*> HumanPlayerStrategy::toAttack(){
    vector<Territory*> terri;
    return terri;
}

//Sorts territory vector from least armies to most
vector<Territory*> HumanPlayerStrategy::toDefend(){
    vector<Territory*> terri = p->getTerritories();

    //TODO: Check that this sorts the territory vector according to number of armies present on each territory
    std::sort(terri.begin(), terri.end(), [](Territory* one, Territory* two ){return (one->getNumArmies() < two -> getNumArmies());});

    return terri;
}

// ============ Cheater Player ==============

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) : PlayerStrategy(p) {
}

bool CheaterPlayerStrategy::issueOrder(){

    vector<Territory*> toConquer =  p->getAdjacentTerritories();
    
    for (Territory* t : toConquer){
        //Remove territory from opponents' territory vector
        Player* oldOwner = t->getOwner();
        oldOwner->removeTerritory(t);

        //Set new Owner
        t->setOwner(p);
        p->addTerritory(t);
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

//TODO: Implement this issueOrder.
bool BenevolentPlayerStrategy::issueOrder(){

    vector<Territory*> terriToDefend = toDefend();


    //TODO: Deploy reinforcements on weakest territories.

    return true;
}

// This method is never Used
vector<Territory*> BenevolentPlayerStrategy::toAttack(){
    vector<Territory*> terri;
    return terri;
}

//Sorts territory vector from least armies to most
vector<Territory*> BenevolentPlayerStrategy::toDefend(){
    vector<Territory*> terri = p->getTerritories();

    //TODO: Check that this sorts the territory vector according to number of armies present on each territory
    std::sort(terri.begin(), terri.end(), [](Territory* one, Territory* two ){return (one->getNumArmies() < two -> getNumArmies());});
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