#include "Orders.h"

#include <stdlib.h>  //rand()

#include <cmath>  //floor()
#include <sstream>
#include <typeinfo>
#include <string>

#include "Cards.h"
#include "Player.h"
#include "PlayerStrategies.h"

// default constructor
Order::Order() {}

// Order copy constructor
Order::Order(const Order &order) {
  std::cout << " Order created with copy constructor" << std::endl;
}

// Order assignment operator
Order &Order::operator=(const Order &order) {
  orderEffect = order.orderEffect;
  return *this;
}

// Order destructor
Order::~Order() { std::cout << "Destroyed Order" << std::endl; }

// Order insertion stream operator
std::ostream &operator<<(std::ostream &out, const Order &o) {
  o.Print(out); // call to virtual function print()
  return out;
}


// Overridden stringtolog methods
string Deploy::stringToLog() { return "type of order: Deploy"; }
string Advance::stringToLog() { return "type of order: Advance"; }
string Bomb::stringToLog() { return "type of order: Bomb"; }
string Blockade::stringToLog() { return "type of order: Blockade"; }
string Airlift::stringToLog() { return "type of order: Airlift"; }
string Negotiate::stringToLog() { return "type of order: Negotiate"; }

// Default OrderList constructor
OrdersList::OrdersList() {
  std::vector<Order *> o;
  this->ListOfOrders = o;
}

// Orderlist copy constructor
OrdersList::OrdersList(const OrdersList &oL) { ListOfOrders = oL.ListOfOrders; }

// Assignment operator
OrdersList &OrdersList::operator=(const OrdersList &oL) {
  if (&oL != this) {
    this->ListOfOrders = oL.ListOfOrders;
  }
  return *this;
}

void OrdersList::move(int initial, int final) {
  // Intial index must be lower than size
  if (initial >= ListOfOrders.size() || initial < 0) return;

  // If final index is out of bounds, use list size as index
  int newIndex = std::min(std::max(final, 0), (int)ListOfOrders.size());

  Order *movedOrder = ListOfOrders[initial];
  ListOfOrders.erase(ListOfOrders.begin() + initial);
  ListOfOrders.insert(ListOfOrders.begin() + newIndex, movedOrder);
}

void OrdersList::remove(int index) {
  // Index must be lower than size
  if (index >= ListOfOrders.size() || index < 0) return;

  ListOfOrders.erase(ListOfOrders.begin() + index);
}

void OrdersList::add(Order *order) {
  // Not sure if we should add to the begining or the end
  ListOfOrders.push_back(order);
  Notify(this);
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &out, const OrdersList &ol) {
  out << "Order list:" << std::endl;

  for (Order *order : ol.ListOfOrders) {
    out << "\t"
       << "Order " << *(order) << " is present in the list,\n";
  }

  return out << std::endl;
}

// execute all orders in the list
void OrdersList::executeOrders() {

  int size = ListOfOrders.size();
  for(int i = 0; i < size; i++){
    cout<< "Executing " << *(ListOfOrders[i]) << endl;
    ListOfOrders[i]->execute();
    delete ListOfOrders[i];

    //remove object from orderlist
    ListOfOrders.erase(ListOfOrders.begin());
  }
}

// subclasses of Order

// constructor for Deploy
Deploy::Deploy(Territory *target, Player *owner, int numOfArmies) {
  Target = target;
  Owner = owner;
  NumOfArmies = numOfArmies;
}

// getter for number of armies
int Deploy::GetNumArmies() { return NumOfArmies; }

// getter for owner of order
Player *Deploy::GetOwner() { return Owner; }

// getter for target territory
Territory *Deploy::GetTarget() { return Target; }

void Deploy::Print(std::ostream &output) const{
  output << "\nDeploy order: "
         << "\n\tOwner: " << this->Owner->getName() << "\n\tTarget" << *(this->Target)
         << "\n\tNum of armies: " << this->NumOfArmies << std::endl;
}

bool Deploy::validate() {
  // If the target territory does not belong to the player that issued the
  // order, the order is invalid
  if (this->GetTarget()->getOwner() != this->GetOwner()) {
    std::cout << "Deploy Order invalid: player must own the target territory " << std::endl << this->GetTarget()->getOwner()->getName()
              << this->GetOwner()->getName() << std::endl;
    return false;
  } else {
    return true;
  }
}

/*A deploy order tells a certain number of army units taken from the
reinforcement pool to deploy to a target territory owned by the player issuing
this order*/
void Deploy::execute() {
  // validate the order before execution
  bool valid = this->validate();
  if (valid) {
    this->Target->addNumArmies(this->GetNumArmies());
  } else {
    std::cout << "Deploying"
              << ": invalid order" << std::endl;
  }
  Notify(this);
}

// end of Deploy class

// Advance class
Advance::Advance(Territory *target, Territory *source, Player *owner,
                 int numOfArmies) {
  Target = target;
  Source = source;
  Owner = owner;
  NumOfArmies = numOfArmies;
}

// Getter methods
int Advance::GetNumArmies() { return NumOfArmies; }

Player *Advance::GetOwner() { return Owner; }

Territory *Advance::GetSource() { return Source; }

Territory *Advance::GetTarget() { return Target; }

// output stream overload
void Advance::Print(std::ostream &output) const {
  output << "\nAdvance order: "
         << "\n\tOwner: " << this->Owner->getName() << "\n\tTarget: " << *(this->Target)
         << "\n\tNum of armies:" << this->NumOfArmies;
  output << "\n\tSource: " << *(this->Source) << std::endl;
}

// Advance order validation
bool Advance::validate() {
  // check if player owns the source territory
  if (this->GetSource()->getOwner() != this->GetOwner()) {
    std::cout << "Advance: "
              << "Invalid Order: Source not owned by player." 
              << "Source: " << this->GetSource()->getOwner()->getName()
              << "Owner: " << this->GetOwner()->getName()
              << std::endl;
    return false;
  }
  // make sure the target is not a diplomatic ally
  std::vector<Player *>::iterator alliesIterate;
  // check if players are allies
  for(int i = 0 ; i < Target->getOwner()->getDiplomaticAllies().size(); i++){
    if(Target->getOwner()->getDiplomaticAllies()[i] == Owner){
            std::cout << "Advance: "
                << "Invalid order: Target is a diplomatic Ally till the end of "
                   "this turn." << endl
                << " Diplomatic Allies: " << endl
                << (Target->getOwner())->getName()
                << std::endl;
      return false;
    }
  }

  // check if territories are adjacent
  bool adj = false;
  // declare vector iterator
  std::vector<Territory *>::iterator iter = this->GetTarget()->adj.begin();
  for (iter; iter != this->GetTarget()->adj.end(); iter++) {
    if (*iter == this->GetSource()) {
      return true;
    }
  }
  std::cout << "Advance: "
            << "Invalid order: Target and source are not adjacent!"
            << std::endl;
  return false;
}

// Advance order execution
void Advance::execute() {
  // verify that order is valid
  bool validate = this->validate();

  if (validate) {
    // if source and target are owned by same player, move players without war;
    if (this->Owner == this->Target->getOwner()) {
      // remove army from source
      this->Source->addNumArmies(this->NumOfArmies * -1);
      // add them to target territory
      this->Target->addNumArmies(this->NumOfArmies);
    } else {
      // target and source are not owner by the same player, this means they go
      // to war

      //If attacked player is neutral, change to aggressive since it was attacked
      Player* attackedPlayer = this->Target->getOwner();
      string stratType = attackedPlayer->getStrategy()->getStrategyString();
      if(stratType == "neutral"){
        cout << "Changing attacked player's strategy from Netural to Aggressive." << endl;
        delete attackedPlayer->getStrategy();
        attackedPlayer->setStrategy(new AggressivePlayerStrategy(attackedPlayer));
      }


      int numAttackArmies = this->NumOfArmies;
      int numDefendArmies = this->GetTarget()->getNumArmies();

      while (numAttackArmies != 0 && numDefendArmies != 0) {
        bool successfulAttackKill =
            (rand() % 100) < 60;  // each attacking army has 60% chance of
                                  // killing one defending army
        bool successfulDefenceKill =
            (rand() % 100) < 70;  // each defending army has 70% chance of
                                  // killing one attacking army

        if (successfulAttackKill) {
          numDefendArmies--;
        }
        if (successfulDefenceKill) {
          numAttackArmies--;
        }
      }
      // loop ends when one of the territories has no more armies left
      // check who won the territory
      if (numDefendArmies > 0) {
        // attack failed -> defendants keep territory
        // set new number of armies
        this->Target->setNumArmies(numDefendArmies);
        int currentArmies = Source->getNumArmies() - this->NumOfArmies;
        this->Source->setNumArmies(currentArmies);

      } else {
        // attack was successful
        std::cout << "Successful attack!" << std::endl;

        //Remove territory from conquered player's territory list.
        this->Target->getOwner()->removeTerritory(this->GetTarget());
        
        //verify if owner still has any territories
        
        //reassign territory
        this->Target->setOwner(this->Owner);
        //add territory to owner
        this->Owner->addTerritory(Target);
        //set number of armies
        this->Target->setNumArmies(numAttackArmies);

        // check if this is the first territory concquered by the player this
        // turn, if yes, player draws card
        if (this->Source->getOwner()->getConcqueredFlag() == false) {
          this->Source->getOwner()->setConcqueredFlag(true);
          //Owner->getHand()->drawCard();  removed --> done in main game loop instead
        }
      }
    }
  }
  Notify(this);
}

// end of Advance order class

// Airlift order implementation
Airlift::Airlift(Territory *target, Territory *source, Player *owner,
                 int numOfArmies) {
  Target = target;
  Source = source;
  Owner = owner;
  NumOfArmies = numOfArmies;
}

bool Airlift::validate() {
  // both source and target territories have to belong to the owner of the order
  if (this->Target->getOwner() != this->Owner) {
    cout << "Order invalid: Target does not belong to the owner." << std::endl;
    return false;
  }
  if (this->Source->getOwner() != this->Owner) {
    cout << "Order invalid: Source does not belong to the owner." << std::endl;
    return false;
  }

  return true;
}

void Airlift::execute() {
  // validate order
  bool validate = this->validate();

  if (validate) {
    // remove armies from source
    Source->addNumArmies(NumOfArmies * -1);
    // move them to target
    Target->addNumArmies(NumOfArmies);
  }
  Notify(this);
}

void Airlift::Print(std::ostream &output) const {
  output << "\nAirlift order:"
         << "\n\tSource: " << *(this->Source) << "\n\tTarget: " << this->Target
         << "\n\tNum of Armies: " << this->NumOfArmies << std::endl;
}

Bomb::Bomb(Territory *target, Player *owner) {
  Target = target;
  Owner = owner;
}

bool Bomb::validate() {
  // target cannot belong to owner
  if (Target->getOwner() == Owner) {
    std::cout << "Order invalid: territory belongs to owner" << std::endl;
    return false;
  }
  // make sure the target is not a diplomatic ally
  std::vector<Player *>::iterator alliesIterate =
      Target->getOwner()->getDiplomaticAllies().begin();
  // check if players are allies

  for(int i = 0; i < Target->getOwner()->getDiplomaticAllies().size(); i++){
    if(Target->getOwner()->getDiplomaticAllies()[i] == Owner){
      std::cout << "Bomb: "
                << "Invalid order: Target is a diplomatic Ally till the end of "
                   "this turn."
                << std::endl;
      return false;
    }
  }
  for (alliesIterate;
       alliesIterate != Target->getOwner()->getDiplomaticAllies().end();
       alliesIterate++) {
    if (*alliesIterate == Owner) {
      std::cout << "Bomb: "
                << "Invalid order: Target is a diplomatic Ally till the end of "
                   "this turn."
                << std::endl;
      return false;
    }
  }

  // target must be adjacent to one of the owner's territory
  // declare vector iterator
  vector<Territory *>::iterator iterate = Target->adj.begin();

  for (iterate; iterate != Target->adj.end(); iterate++) {
    if ((*iterate)->getOwner() == Owner) {
      return true;
    }
  }
  std::cout << "Bomb: "
            << "Invalid order: Target and source are not adjacent!"
            << std::endl;
  return false;
}

void Bomb::execute() {
  // validate the order
  bool validate = this->validate();

  if (validate) {
    // removes half of the army on the territory, rounded down.
    int numOfarmies = std::floor(Target->getNumArmies() / 2.0);
    Target->setNumArmies(numOfarmies);
  }
  Notify(this);
}

void Bomb::Print(std::ostream &output) const {
  output << "Bomb Order:\n\tOwner:  " << this->Owner->getName() << "\n\tTarget: " << *(this->Target)
         << std::endl;
}

// end of Bomb order implementation

// Blockade order implementation
Blockade::Blockade(Territory *target, Player *owner, Player *neutral) {
  Target = target;
  Owner = owner;
  NeutralPlayer = neutral;
}

// blockade validate implementation
bool Blockade::validate() {
  // target cannot belong to another player

  if (Target->getOwner() != Owner) {
    return false;
  }
  return true;
}

// Blockage execute implementation
void Blockade::execute() {
  // validate order
  bool validate = this->validate();

  if (validate) {
    if (NeutralPlayer == NULL) {
      NeutralPlayer = new Player("neutral");
    }
    // double the num of armies
    int numArmies = Target->getNumArmies() * 2;
    Target->setNumArmies(numArmies);

    // give territory to neutral player
    Target->setOwner(this->NeutralPlayer);
  }
  Notify(this);
}

void Blockade::Print(std::ostream &output) const {
  output << "Blockade Order:\n\t" << this->Owner->getName() << "\n\tTarget: " << *(this->Target)
         << std::endl;
}

// end of blockade implementation

// negotiate order implementation
Negotiate::Negotiate(Territory *target, Player *owner) {
  Target = target;
  Owner = owner;
}

// validate negotiate implementation
bool Negotiate::validate() {
  // target must be an enemy
  if (Target->getOwner() == Owner) {
    std::cout << "Negotiate "
              << "Invalid order: Owner cannot own the target territory"
              << std::endl;
    return false;
  }
  return true;
}

// execute negotiate implementation
void Negotiate::execute() {
  // validate order
  bool validate = this->validate();

  if (validate) {
    // make both players diplomatic allies for the rest of the turn
    Owner->addDiplomaticAlly(Target->getOwner());
    Target->getOwner()->addDiplomaticAlly(Owner);
  }
  Notify(this);
}

void Negotiate::Print(std::ostream &output) const {
  output << "Negotiate Order:\n\tTarget: " << *(this->Target)
         << "\n\tOwner: " << this->Owner->getName() << std::endl;
}

// end of negotiate order implementation

// overidden stringtolog method for orderslist
string OrdersList::stringToLog() {
  string s = ListOfOrders.at((this->ListOfOrders).size() - 1)->stringToLog();
  // this->ListOfOrders[(this->ListOfOrders).size()-1] + "\n";
  /*
  for (int i = 0; i < (this->ListOfOrders).size(); i++) {
    s += "type of order " + i;
    s += " :" + ListOfOrders.at(i)->stringToLog() + "\n";
  }
  */
  return s;
}
