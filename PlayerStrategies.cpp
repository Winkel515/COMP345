#include "PlayerStrategies.h"
#include <vector>
using std::vector;
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;
#include "Map.h"
#include "Player.h"
#include "Orders.h"

PlayerStrategy::PlayerStrategy(Player* p){
    this->p = p;
}

// ============ Human Player ==============

HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p) {}

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

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) : PlayerStrategy(p) {}

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

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p) {}

bool AggressivePlayerStrategy::issueOrder(){

    vector<Territory*> territories = toDefend();
    Territory* strongestTerri = territories.front();
    int reinforcements = p->getReinforcements();

    if(reinforcements > 0){
        p->getOrderList()->add(new Deploy(strongestTerri, p, reinforcements));
        p->addReinforcements(reinforcements * -1);
        //TODO JOHN: Once merged with mainGameLoopFix, Add Player Name
        cout << "Player is issuing a Deploy Order: " << reinforcements << " armies to territory " << strongestTerri->name << "." << endl;
        return true;
    }

    //TODO: Implement Advance Orders (Check if it can advance into an enemy territory. If not, advance towards an enemy territory)
    //TODO: Implement Bomb Orders
    //TODO: Implement Airlift Order

    return false;
}

vector<Territory*> AggressivePlayerStrategy::toAttack(){

    //TODO: return the strongest territory's adjacent territories
    vector<Territory*> terri;
    return terri;
}

// Returns vector of territories from strongest to weakest
vector<Territory*> AggressivePlayerStrategy::toDefend(){
    vector<Territory*> terri = p->getTerritories();
    //TODO: Check that this sorts the territory vector according to number of armies present on each territory
    std::sort(terri.begin(), terri.end(), [](Territory* one, Territory* two ){return (one->getNumArmies() > two -> getNumArmies());});
    return terri;
}

// ============ Benevolent Player ==============

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p) {}

//TODO: Finish this issueOrder.
bool BenevolentPlayerStrategy::issueOrder(){

    vector<Territory*> territories = toDefend();

    Territory* weakestTerri = territories.front();
    int reinforcements = p->getReinforcements();

    // Create Deploy order, adding all territories to its weakest territory 
    if (reinforcements > 0){
        p->getOrderList()->add(new Deploy(weakestTerri, p, reinforcements));
        p->addReinforcements(reinforcements * -1);
        //TODO JOHN: Once merged with mainGameLoopFix, Add Player Name
        cout << "Player is issuing a Deploy Order: " << reinforcements << " armies to territory " << weakestTerri->name << "." << endl;
        return true;
    }

        //TODO: Add Advance implementation
        //TODO: Add Airlift implementation
        //TODO: Add Diplomacy implementation
        //TODO: Add Reinforcement card implementation

    return false;
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

//TODO: Somehow change to aggressive if attacked. Where should this be implemented?

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : PlayerStrategy(p) {}

//Never issues orders
bool NeutralPlayerStrategy::issueOrder(){
    return false;
}

//Never Used
vector<Territory*> NeutralPlayerStrategy::toAttack(){
    vector<Territory*> terri;
    return terri;
}

//Never Used
vector<Territory*> NeutralPlayerStrategy::toDefend(){
    vector<Territory*> terri;
    return terri;
}