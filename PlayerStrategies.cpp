#include "PlayerStrategies.h"
#include <vector>
using std::vector;
#include <algorithm>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "Map.h"
#include "Player.h"
#include "Orders.h"
#include "Cards.h"

PlayerStrategy::PlayerStrategy(Player* p){
    this->p = p;
}

// ============ Human Player ==============

HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p) {}

bool HumanPlayerStrategy::issueOrder(){
    cout << "Issue order menu: \nPlease choose an option (enter 1-6):\n" << endl;
    cout << "\n\t1: Deploy Order" << "\n\t2: Advance Order" << "\n\t3: Airlift Order" << "\n\t4: Bomb Order" << "\n\t5: Blockade Order" << "\n\t6: Negotiate Order" << endl;

    int choice; 
    bool validChoice = false;
    while(!validChoice){
        cin >> choice;
        if(choice < 6 and choice > 1){
            validChoice = true;
        }
    }
    //Deploy Order
    if(choice == 1){
        cout << "Deploy Order chosen: " << p->getReinforcements() << "available units" << endl;
        vector<Territory*> territoriesToDefend = toDefend();
        cout << "Choose one of the following territories (enter territory #): " << endl;
        for(int i = 0; i < territoriesToDefend.size(); i++){
            cout << "Territory # " << i << ": "<< *(territoriesToDefend.at(i)) << endl;
        }
        int tNum;
        validChoice = false;
        Territory* deployToTerritory;
        while(!validChoice){
            cin >> tNum;
            if(tNum >= 0 and tNum < territoriesToDefend.size()){
                validChoice = true;
                deployToTerritory = territoriesToDefend.at(tNum);
            } else {
                cout << "invalid choice!! try again" << endl;
            }
        }
        //choose number of reinforcements to deploy
        cout << "Choose number of territories to deploy: " << p->getReinforcements() << " available" << endl;
        validChoice = false;
        while(!validChoice){
            cin >> tNum;
            if(tNum >= 0 and tNum < p->getReinforcements()){
                validChoice = true;
            } else {
                cout << "invalid choice!! try again" << endl;
            }
        }
        //add order to order list
        p->getOrderList()->add(new Deploy(deployToTerritory, p, tNum));
        return true;

    } else if(choice == 2){
        //advance order 
        cout << "Advance order chosen:" << endl;
        vector<Territory*> available = toDefend();

        //choose territory to advance with
        cout << "Choose territory to advance with (enter territory #): " << endl;
        for(int i = 0; i < available.size(); i++){
            cout << "Territory # " << i << ": " << *(available.at(i)) << endl;
        }
        int tAdv;
        validChoice = false;
        Territory* advanceTerritory;
        while(!validChoice){
            cin >> tAdv;
            if(tAdv >= 0 and tAdv < available.size()){
                validChoice = true;
                advanceTerritory = available.at(tAdv);
            } else {
                cout << "Invalid choice!! try again" << endl;
            }
        }

        //choose attack or regular advance
        validChoice = false;
        cout << "Choose attack(1) advance or friendly(2) advance: (enter 1 or 2)" << endl;
        while(!validChoice){
            cin >> tAdv;
            if(tAdv != 1 and tAdv != 2){
                cout << "Invalid choice!! try again" << endl;
            } else {
                validChoice = true;
            }
        }

        if(tAdv == 1){
            //attack advance
            int attackchoice;
            cout << "Choose territory to attack (enter territory #): " << endl;
            vector<Territory*> attackable = toAttack();
            for(int i = 0; i < attackable.size(); i++){
                cout << "Territory # " << i << ": " << *(attackable.at(i)) << endl;
            }
            Territory* attackTerr;
            validChoice = false;
            while(!validChoice){
                cin >> attackchoice;
                if(attackchoice >= 0 and attackchoice < attackable.size()){
                    attackTerr = attackable.at(attackchoice);
                    validChoice = true;
                } else {
                    cout << "Invalid choice!! try again" << endl;
                }
            }

            //choose number of armies to advance
            int attackNum;
            cout << "Choose number of armies to send: " << advanceTerritory->getNumArmies() << " available" << endl;

            validChoice = false;
            while(!validChoice){
                cin >> attackNum;
                if(attackNum >= 0 and attackNum <= advanceTerritory->getNumArmies()){
                    validChoice = true;
                }
            }

            //create attack order
            p->getOrderList()->add(new Advance(attackTerr, advanceTerritory, p, attackNum));
            return true;
        } else {
            //friendly advance
            cout << "Choose friendly territory to advance to (enter territory#): " << endl;
            for(int i = 0; i < advanceTerritory->adj.size(); i++){
                if(advanceTerritory->adj.at(i)->getOwner() == p){
                  cout << "Territory # " << i << ": " << *(advanceTerritory->adj.at(i)) << endl;
                } 
            }
            int targetChoice;
            validChoice = false;
            while(!validChoice){
                cin >> targetChoice;
                if(targetChoice >= 0 and targetChoice < advanceTerritory->adj.size()){
                    //check if friendly territory
                    if(p == advanceTerritory->adj.at(targetChoice)->getOwner()){
                        validChoice = true;
                    } else {
                        cout << "Invalid choice!! try again" << endl;
                    }
                } else {
                    cout << "Invalid choice!! try again" << endl;
                }
            }
            //get target terr
            Territory* targetTerr = advanceTerritory->adj.at(targetChoice);

            //choose number of units to advance
            int advanceNum;
            cout << "Choose number of armies to send: " << advanceTerritory->getNumArmies() << " available" << endl;

            validChoice = false;
            while(!validChoice){
                cin >> advanceNum;
                if(advanceNum >= 0 and advanceNum <= advanceTerritory->getNumArmies()){
                    validChoice = true;
                }
            }

            //create advance order
            p->getOrderList()->add(new Advance(targetTerr, advanceTerritory, p,advanceNum));
            return true;
         }

    } else if(choice == 3){
        //check if player has airlift card
        bool hasCard = false;
        for(int i = 0; i < p->getHand()->getCards().size(); i++){
            if(p->getHand()->getCards().at(i)->GetType() == Card::Airlift){
                hasCard = true;
                p->getHand()->getCards().at(i)->play(p->getHand()->getDeck());
                //remove card from player hand
                p->getHand()->getCards().erase(p->getHand()->getCards().begin() + i);
            }
        }
        if(hasCard){
            //Airlift
            cout << "Airlift order chosen:" << endl;
            vector<Territory*> available = toDefend();

            //choose territory to airlift
            cout << "Choose territory to airlift (enter territory #): " << endl;
            for(int i = 0 ; i < available.size(); i++){
                cout << "Territory # " << i << ": " << *(available.at(i)) << endl;
            }
            int airChoice;
            validChoice = false;
            Territory* airliftTerr;
            while(!validChoice){
                cin >> airChoice;
                if(airChoice >= 0 and airChoice < available.size()){
                    validChoice = true;
                    airliftTerr = available.at(airChoice);
                } else {
                    cout << "Invalid choice!! try again" << endl;
                }
            }

            //choose target territory
            Territory* airliftTarget;
            cout << "Choose target territory (enter territory #): " << endl;
            for(int i = 0 ; i < available.size(); i++ ){
                if(i != airChoice){
                    cout << "Territory #: " << *(available.at(i)) << endl;
                }
            }
            int targetChoice;
            validChoice = false;
            while(!validChoice){
                cin >> targetChoice;
                if(targetChoice >= 0 and targetChoice < available.size() and targetChoice != airChoice){
                    validChoice = true;
                    airliftTarget = available.at(targetChoice);
                } else {
                    cout << "Invalid choice!! try again" << endl;
                }
            }

                //choose number of armies to airlift
                int airliftNum;
                cout << "Choose number of armies to send: " << airliftTerr->getNumArmies() << " available" << endl;

                validChoice = false;
                while(!validChoice){
                    cin >> airliftNum;
                    if(airliftNum >= 0 and airliftNum <= airliftTerr->getNumArmies()){
                        validChoice = true;
                    }
                }

            //create airlift order
            p->getOrderList()->add(new Airlift(airliftTarget, airliftTerr, p, airliftNum));
            return true;
        } else {
            cout << "Invalid order. Player does not have airlift card" << endl;
        }   
    
    } else if (choice == 4){
        cout << "Bomb Order chosen: " << endl;
        //check if player has bomb card
        bool hasCard = false;
        for(int i = 0; i < p->getHand()->getCards().size(); i++){
            if(p->getHand()->getCards().at(i)->GetType() == Card::Bomb){
                hasCard = true;
                p->getHand()->getCards().at(i)->play(p->getHand()->getDeck());
                //remove card from player hand
                p->getHand()->getCards().erase(p->getHand()->getCards().begin() + i);
            }
        }

        if(hasCard){
            //choose target to bomb
            int attackChoice;
            cout << "Choose territory to attack (enter territory #): " << endl;
            vector<Territory*> attackable = toAttack();
            for(int i = 0; i < attackable.size(); i++){
                cout << "Territory # " << i << ": " << *(attackable.at(i)) << endl;
            }
            Territory* bombTerr; 
            validChoice = false;
            while(!validChoice){
                cin >> attackChoice;
                if(attackChoice >= 0 and attackChoice < attackable.size()){
                    bombTerr = attackable.at(attackChoice);
                    validChoice = true;
                }
            }

            //create bomb order
            p->getOrderList()->add(new Bomb(bombTerr, p));
            return true;
        } else {
            cout << "Invalid order, player does not have bomb card" << endl;
            return false;
        }

    } else if (choice == 5){
        //blockade order
        //check if player has blockade card
        bool hasCard = false;
        for(int i = 0; i < p->getHand()->getCards().size(); i++){
            if(p->getHand()->getCards().at(i)->GetType() == Card::Blockade){
                hasCard = true;
                p->getHand()->getCards().at(i)->play(p->getHand()->getDeck());
                //remove card from player hand
                p->getHand()->getCards().erase(p->getHand()->getCards().begin() + i);
            }
        }

        if(hasCard){
            //choose territory to blockade
            cout << "Choose territory to blockade (enter territory #): " << endl;
            vector<Territory*> ownerTerrs = toDefend();
            for(int i = 0; i < ownerTerrs.size(); i++){
                cout << "Territory # " << i << ": " << *(ownerTerrs.at(i)) << endl;
            }
            Territory* blockadeTerr;
            validChoice = false;
            int blockChoice;
            while(!validChoice){
                cin >> blockChoice;
                if(blockChoice >= 0 and blockChoice < ownerTerrs.size()){
                    validChoice = true;
                    blockadeTerr = ownerTerrs.at(blockChoice);
                } else {
                    cout << "invalid choice!! try again" << endl;
                }
            }

            //create blockade order
            p->getOrderList()->add(new Blockade(blockadeTerr, p, p->neutralPlayer));
            return true;
        } else {
            cout << "Invalid order. player does not have blockade card" << endl;
            return false;
        }
    } else if(choice == 6){
        //negotiate order
        cout << "Negotiate order chosen" << endl;
        //check if player has diplomacy card
        bool hasCard = false;
        for(int i = 0; i < p->getHand()->getCards().size(); i++){
            if(p->getHand()->getCards().at(i)->GetType() == Card::Diplomacy){
                hasCard = true;
                p->getHand()->getCards().at(i)->play(p->getHand()->getDeck());
                //remove card from player hand
                p->getHand()->getCards().erase(p->getHand()->getCards().begin() + i);
            }
        }

        if(hasCard){
            //choose player to negotiate with
            vector<Territory*> enemies = toAttack();
            cout << "Choose player to negotiate with by choosing one of their territories below (enter territory #): " << endl;
            for(int i = 0; i < enemies.size(); i++){
                cout << "Territory # " << i << ": " << *(enemies.at(i)) << endl;
            }
            int terrChoice;
            validChoice = false;
            Territory* negotiatePlayerTerr;
            while(!validChoice){
                cin >> terrChoice;
                if(terrChoice >= 0 and terrChoice < enemies.size()){
                    negotiatePlayerTerr = enemies.at(terrChoice);
                    validChoice = true;
                }
            }

            //create negotiate order
            p->getOrderList()->add(new Negotiate(negotiatePlayerTerr, p));
            return true;
        } else {
            cout << "Invalid order: player does not have diplomacy card" << endl;
            return false;
        }

    } else {
        cout << "Invalid order" << endl;
        return false;
    }
}

vector<Territory*> HumanPlayerStrategy::toAttack(){
    vector<Territory*> terri = p->getTerritories();

    //sort territories from strongest to weakest
    std::sort(terri.begin(), terri.end(), [](Territory* one, Territory* two){return (one->getNumArmies() > two->getNumArmies());});

    //get adjacent territories from enemies
    vector<Territory*> attackableTerritories;
    for(int i = 0; i < terri.size(); i++){
        for(int j = 0; j < terri.at(i)->adj.size(); j++){
            if(terri.at(i)->adj.at(j)->getOwner() != p){
                attackableTerritories.push_back(terri.at(i)->adj.at(j));
            }
        }
    }

    //sort enemy territories from weakest to strongest
    std::sort(terri.begin(), terri.end(), [](Territory* one, Territory* two){return (one->getNumArmies() < two->getNumArmies());});

    return attackableTerritories;
}

//Sorts territory vector from least armies to most
vector<Territory*> HumanPlayerStrategy::toDefend(){
    vector<Territory*> terri = p->getTerritories();

    //sort players by number of armies
    std::sort(terri.begin(), terri.end(), [](Territory* one, Territory* two){return (one->getNumArmies() < two->getNumArmies());});

    return terri;
}

string HumanPlayerStrategy::getStrategyString(){
    return "human";
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

string CheaterPlayerStrategy::getStrategyString(){
    return "cheater";
}

// ============ Aggressive Player ==============

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p) {}

bool AggressivePlayerStrategy::issueOrder(){

    vector<Territory*> territories = toDefend();
    Territory* strongestTerri = territories.front();
    int reinforcements = p->getReinforcements();

    if(reinforcements > 0){
        //Deploy Reinforcements
        p->getOrderList()->add(new Deploy(strongestTerri, p, reinforcements));
        p->addReinforcements(reinforcements * -1);
        cout << "Player " << p->getName() << " is issuing a Deploy Order: " << reinforcements << " armies to territory " << strongestTerri->name << "." << endl;
        return true;
    }

    //Bomb check
    vector<Card*> hand = p->getHand()->getCards();
    for(Card* c : hand){
        //if a card is a bomb, play it
        if (c->GetType() == 0){

            vector<Territory*> targets = p->getAdjacentTerritories();
            Territory* target = targets.at(0);
            p->getOrderList()->add(new Bomb(target, p));
            cout << p->getName() << " is bombing " << *target << endl;

            //Play card, remove from hand
            c->play(p->getHand()->getDeck());
            hand.erase(find(hand.begin(),hand.end(), c), hand.end());
            p->getHand()->setCards(hand);

            return true;
        }
    }

    
    //Advance only once
    vector<Territory*> strAdjacent = strongestTerri->adj;
    if(strongestTerri->getNumArmies() != 0){
        //Choose a territory to advance to.
        Territory* toAdvanceTo = strAdjacent.at(0);
        for(Territory* t : strAdjacent){
            if(!(t->getOwner() == p)){
                toAdvanceTo = t;
            }
        }
        //Advance once only
        cout << "Player " << p->getName() << " is issuing an Advance Order: " << strongestTerri->getNumArmies()
        << " armies to territory " << toAdvanceTo->name << " from " << strongestTerri->name << "." << endl;
        p->getOrderList()->add(new Advance(toAdvanceTo, strongestTerri, p, strongestTerri->getNumArmies()));
    }
    return false;
}

//Returns the strongest territories neighbours which are owned by another player
vector<Territory*> AggressivePlayerStrategy::toAttack(){

    vector<Territory*> territories = toDefend();
    Territory* strongestTerri = territories.front();
    vector<Territory*> strAdjacent = strongestTerri->adj;

    // Removes territories which are owned by current player.
    // TODO: Test that this works
    strAdjacent.erase(std::remove_if(
        strAdjacent.begin(), 
        strAdjacent.end(), 
        [this] (Territory* t) {return t->getOwner() == p;}
        ), 
        strAdjacent.end());

    return strAdjacent;
}

// Returns vector of territories from strongest to weakest
vector<Territory*> AggressivePlayerStrategy::toDefend(){
    vector<Territory*> terri = p->getTerritories();
    //TODO: Check that this sorts the territory vector according to number of armies present on each territory
    std::sort(terri.begin(), terri.end(), [](Territory* one, Territory* two ){return (one->getNumArmies() > two -> getNumArmies());});
    return terri;
}

string AggressivePlayerStrategy::getStrategyString(){
    return "aggressive";
}

// ============ Benevolent Player ==============

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p) {}

//TODO: Finish this issueOrder.
bool BenevolentPlayerStrategy::issueOrder(){

    vector<Territory*> territories = toDefend();

    if(territories.size() > 0){

        Territory* weakestTerri = territories.at(0);
        int reinforcements = p->getReinforcements();

        // Create Deploy order, adding all territories to its weakest territory 
        if (reinforcements > 0){
            p->getOrderList()->add(new Deploy(weakestTerri, p, reinforcements));
            p->addReinforcements(reinforcements * -1);
            //TODO JOHN: Once merged with mainGameLoopFix, Add Player Name
            cout << "Player " << p->getName() << " is issuing a Deploy Order: " << reinforcements << " armies to territory " << weakestTerri->name << "." << endl;
            return true;
        }
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

string BenevolentPlayerStrategy::getStrategyString(){
    return "benevolent";
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

string NeutralPlayerStrategy::getStrategyString(){
    return "neutral";
}