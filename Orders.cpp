#include "Orders.h"

#include <sstream>
#include <stdlib.h> //rand()

using namespace std;

// default constructor
Order::Order() {}

// Order copy constructor
Order::Order(const Order &order) {
  cout << " Order created with copy constructor" << endl;
}

// Order assignment operator
Order &Order::operator=(const Order &order) {
  orderEffect = order.orderEffect;
  return *this;
}

// Order destructor
Order::~Order() { cout << "Destroyed Order" << endl; }

// Order insertion stream operator
ostream &operator<<(ostream &out, const Order &o) {
  out << "Order insertion stream called" << endl;
  return out;
}


// Default OrderList constructor
OrdersList::OrdersList() {
  vector<Order *> o;
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
  int newIndex = min(max(final, 0), (int)ListOfOrders.size());

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
ostream &operator<<(ostream &o, const OrdersList &ol) {
  stringstream ss;

  ss << "Order list:" << endl;

  for (Order *order : ol.ListOfOrders) {
    ss << "\t"
       << "Order " << order->GetType() << " is present in the list,\n";
  }

  return o << ss.str() << endl;
}

// execute all orders in the list
void OrdersList::executeOrders() {
  for (Order *order : ListOfOrders) {
    order->execute();
  }
}


//subclasses of Order

//constructor for Deploy
Deploy::Deploy(Territory* target, Player* owner, int numOfArmies){
  Target = target;
  Owner = owner;
  NumOfArmies = numOfArmies;
}

//getter for number of armies
int Deploy::GetNumArmies(){ return NumOfArmies;}

//getter for owner of order
Player* Deploy::GetOwner(){ return Owner;}

//getter for target territory
Territory* Deploy::GetTarget(){ return Target; }

ostream &operator<<(ostream &output, const Deploy &o){
  output << "\nDeploy order: " << "\n\tOwner: " << *o.Owner << "\n\tTarget" << *o.Target << "\n\tNum of armies:" <<o.NumOfArmies << endl;
  return output;
}

bool Deploy::validate(){
  //If the target territory does not belong to the player that issued the order, the order is invalid
  if(this->GetTarget()->getOwner() != this->GetOwner()){
    cout << "Order invalid: player must own the target territory" << endl;
    return false;
  } else {
    return true;
  }
}

/*A deploy order tells a certain number of army units taken from the reinforcement pool to deploy to
a target territory owned by the player issuing this order*/
void Deploy::execute(){
  //validate the order before execution
  bool valid = this->validate();
  if(valid){
    this->Target->addNumArmies(this->GetNumArmies());
  } else {
    cout << "Invalid order" << endl;
  }
}

ostream &operator<<(ostream &out, const Deploy &o){
  out << "Deploy" << endl;
  return out;
}
//end of Deploy class

//Advance class
Advance::Advance(Territory* target, Territory* source, Player* owner, int numOfArmies){
  Target = target;
  Source = source;
  Owner = owner;
  NumOfArmies = numOfArmies;
}

//Getter methods
int Advance::GetNumArmies(){return NumOfArmies;}

Player* Advance::GetOwner(){ return Owner;}

Territory* Advance::GetSource(){ return Source;}

Territory* Advance::GetTarget(){ return Target; }

//output stream overload
ostream &operator<<(ostream &output, const Advance &o){
  output << "\nAdvance order: " << "\n\tOwner: " << *o.Owner << "\n\tTarget" << *o.Target << "\n\tNum of armies:" <<o.NumOfArmies;
  output << "\n\tSource: " <<  *o.Source << endl;
  return output;
}

//Advance order validation
bool Advance::validate(){
  //check if player owns the source territory
  if(this->GetSource()->getOwner() != this->GetOwner()){
    cout << "Invalid Order: Source not owned by player." << endl;
    return false;
  }

  //check if territories are adjacent
  bool adj = false;
  //declare vector iterator
  vector<Territory*>::iterator iter = this->GetTarget()->adj.begin();
  for(iter; iter < this->GetTarget()->adj.end(); iter++){
    if(*iter == this->GetSource()){
      adj = true;
    }
  }
  if(adj == false){
    cout << "Invalid order: Target and source are not adjacent!" << endl;
    return false;
  }

  return true;
}

//Advance order execution
void Advance::execute(){
  //verify that order is valid
  bool validate = this->validate();

  if(validate){
    //if source and target are owned by same player, move players without war;
    if(this->Owner == this->Target->getOwner()){
      //remove army from source
      this->Source->addNumArmies(this->NumOfArmies * -1);
      //add them to target territory
      this->Target->addNumArmies(this->NumOfArmies);
    } else {
      //target and source are not owner by the same player, this means they go to war
      int numAttackArmies = this->NumOfArmies;
      int numDefendArmies = this->GetTarget()->getNumArmies();

      while(numAttackArmies != 0 && numDefendArmies != 0 ){
      bool successfulAttackKill = (rand() % 100) < 60; //each attacking army has 60% chance of killing one defending army
      bool successfulDefenceKill = (rand() % 100) < 70; //each defending army has 70% chance of killing one attacking army

      if(successfulAttackKill){
        numDefendArmies--;
      }
      if(successfulDefenceKill){
        numAttackArmies--;
      }

    }
    //loop ends when one of the territories has no more armies left
    //check who won the territory
    if(numDefendArmies > 0){
      //attack failed -> defendants keep territory
      //set new number of armies
      this->Target->setNumArmies(numDefendArmies);
      this->Source->addNumArmies(this->NumOfArmies * -1);

    } else {
      //attack was successful
      this->Source->setOwner(this->Owner);
      this->Source->setNumArmies(numAttackArmies);

      
    }
  }
}

