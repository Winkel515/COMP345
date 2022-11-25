#include "PlayerStrategies.h"
#include <vector>
#include "Map.h"

using std::vector;

PlayerStrategy::PlayerStrategy(Player* p){
    this->p = p;
}

HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p){}
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) : PlayerStrategy(p){}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p){}
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : PlayerStrategy(p){}
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p){}

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

bool CheaterPlayerStrategy::issueOrder(){

    return true;
}

vector<Territory*> CheaterPlayerStrategy::toAttack(){
    vector<Territory*> terri;
    return terri;
}

vector<Territory*> CheaterPlayerStrategy::toDefend(){
    vector<Territory*> terri;
    return terri;
}

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