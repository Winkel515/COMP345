#include "Orders.h"

#include <stdlib.h>  //rand()

#include <cmath>  //floor()
#include <sstream>

#include "Cards.h"
#include "Player.h"

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
  out << "Order insertion stream called" << std::endl;
  return out;
}

// overloaded to string method
string Order::stringToLog() {
  string s = "Order class\ntype of order: Order";
  return s;
}
string Deploy::stringToLog() { return "Order class\ntype of order: Deploy"; }
string Advance::stringToLog() { return "Order class\ntype of order: Advance"; }
string Bomb::stringToLog() { return "Order class\ntype of order: Bomb"; }
string Blockade::stringToLog() {
  return "Order class\ntype of order: Blockade";
}
string Airlift::stringToLog() { return "Order class\ntype of order: Airlift"; }
string Negotiate::stringToLog() {
  return "Order class\ntype of order: Negotiate";
}

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

  // Delete the pointer
  delete ListOfOrders[index];
  ListOfOrders.erase(ListOfOrders.begin() + index);
}

void OrdersList::add(Order *order) {
  // Not sure if we should add to the begining or the end
  ListOfOrders.push_back(order);
  Notify(this);
}

// OrderList destructor
OrdersList::~OrdersList() {
  // Remove all the pointers in the vector
  for (int i = 0; i < this->ListOfOrders.size(); i++) {
    delete this->ListOfOrders[i];
    this->ListOfOrders[i] = nullptr;
  }
  this->ListOfOrders.clear();
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &o, const OrdersList &ol) {
  std::stringstream ss;

  ss << "Order list:" << std::endl;

  for (Order *order : ol.ListOfOrders) {
    ss << "\t"
       << "Order " << *order << " is present in the list,\n";
  }

  return o << ss.str() << std::endl;
}

// execute all orders in the list
void OrdersList::executeOrders() {
  for (Order *order : ListOfOrders) {
    order->execute();
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

std::ostream &operator<<(std::ostream &output, const Deploy &o) {
  output << "\nDeploy order: "
         << "\n\tOwner: " << *o.Owner << "\n\tTarget" << *o.Target
         << "\n\tNum of armies:" << o.NumOfArmies << std::endl;
  return output;
}

bool Deploy::validate() {
  // If the target territory does not belong to the player that issued the
  // order, the order is invalid
  if (this->GetTarget()->getOwner() != this->GetOwner()) {
    std::cout << "Order invalid: player must own the target territory"
              << std::endl;
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
    std::cout << "Invalid order" << std::endl;
  }
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
std::ostream &operator<<(std::ostream &output, const Advance &o) {
  output << "\nAdvance order: "
         << "\n\tOwner: " << *o.Owner << "\n\tTarget" << *o.Target
         << "\n\tNum of armies:" << o.NumOfArmies;
  output << "\n\tSource: " << *o.Source << std::endl;
  return output;
}

// Advance order validation
bool Advance::validate() {
  // check if player owns the source territory
  if (this->GetSource()->getOwner() != this->GetOwner()) {
    std::cout << "Invalid Order: Source not owned by player." << std::endl;
    return false;
  }
  // make sure the target is not a diplomatic ally
  std::vector<Player *>::iterator alliesIterate =
      Target->getOwner()->getDiplomaticAllies().begin();
  // check if players are allies
  for (alliesIterate;
       alliesIterate != Target->getOwner()->getDiplomaticAllies().end();
       alliesIterate++) {
    if (*alliesIterate == Owner) {
      std::cout << "Invalid order: Target is a diplomatic Ally till the end of "
                   "this turn."
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
  std::cout << "Invalid order: Target and source are not adjacent!"
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
        this->Source->addNumArmies(this->NumOfArmies * -1);

      } else {
        // attack was successful
        this->Source->setOwner(this->Owner);
        this->Source->setNumArmies(numAttackArmies);

        // check if this is the first territory concquered by the player this
        // turn, if yes, player draws card
        if (this->Source->getOwner()->getConcqueredFlag() == false) {
          this->Source->getOwner()->setConcqueredFlag(true);
          Owner->getHand()->drawCard();
        }
      }
    }
  }
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
}

std::ostream &operator<<(std::ostream &output, const Airlift &o) {
  output << "\nAirlift order:"
         << "\n\tSource: " << *o.Source << "\n\tTarget: " << *o.Target
         << "\n\tNum of Armies: " << o.NumOfArmies << std::endl;
  return output;
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
  for (alliesIterate;
       alliesIterate != Target->getOwner()->getDiplomaticAllies().end();
       alliesIterate++) {
    if (*alliesIterate == Owner) {
      std::cout << "Invalid order: Target is a diplomatic Ally till the end of "
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
  std::cout << "Invalid order: Target and source are not adjacent!"
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
}

std::ostream &operator<<(std::ostream &output, const Bomb &o) {
  output << "Bomb Order:\n\tOwner:  " << *o.Owner << "\n\tTarget: " << *o.Target
         << std::endl;
  return output;
}

// end of Bomb order implementation

// Blockade order implementation
Blockade::Blockade(Territory *target, Player *owner, Player *neutral) {
  Target = target;
  Owner = owner;
  NeutralPlayer = neutral;
}

bool Blockade::validate() {
  // target cannot belong to another player
  if (Target->getOwner() != Owner) {
    return false;
  }
  return true;
}

void Blockade::execute() {
  // validate order
  bool validate = this->validate();

  if (validate) {
    // double the num of armies
    int numArmies = Target->getNumArmies() * 2;
    Target->setNumArmies(numArmies);

    // give territory to neutral player
    Target->setOwner(this->NeutralPlayer);
  }
}

std::ostream &operator<<(std::ostream &output, const Blockade &o) {
  output << "Blockade Order:\n\t" << *o.Owner << "\n\tTarget: " << *o.Target
         << std::endl;
  return output;
}

// end of blockade implementation

// negotiate order implementation
Negotiate::Negotiate(Territory *target, Player *owner) {
  Target = target;
  Owner = owner;
}

bool Negotiate::validate() {
  // target must be an enemy
  if (Target->getOwner() == Owner) {
    std::cout << "Invalid order: Owner cannot own the target territory"
              << std::endl;
    return false;
  }
  return true;
}

void Negotiate::execute() {
  // validate order
  bool validate = this->validate();

  if (validate) {
    // make both players diplomatic allies for the rest of the turn
    Owner->addDiplomaticAlly(Target->getOwner());
    Target->getOwner()->addDiplomaticAlly(Owner);
  }
}

std::ostream &operator<<(std::ostream &output, const Negotiate &o) {
  output << "Negotiate Order:\n\tTarget: " << *o.Target
         << "\n\tOwner: " << *o.Owner << std::endl;
  return output;
}

// end of negotiate order implementation
string OrdersList::stringToLog() {
  string s = "OrdersList class\ntype of order ";
  // this->ListOfOrders[(this->ListOfOrders).size()-1] + "\n";
  for (int i = 0; i < (this->ListOfOrders).size(); i++) {
    s += "type of order " + i;
    s += " :" + ListOfOrders.at(i)->stringToLog() + "\n";
  }
  return s;
}
