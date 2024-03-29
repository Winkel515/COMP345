#ifndef Orders_H
#define Orders_H
#include <iostream>
#include <string>
#include <vector>

#include "Map.h"

class Player;

#include "LoggingObserver.h"

class Order : public Subject, public ILoggable {
 public:
  Order();
  Order(const Order& o);
  Order& operator=(const Order& copy);
  ~Order();
  friend std::ostream& operator<<(std::ostream& output, const Order& o);
  virtual bool validate() = 0;       // pure virtual
  virtual void execute() = 0;        // pure virtual
  virtual string stringToLog() = 0;  // pure virtual

 private:
  std::string orderEffect;
  virtual void Print(std::ostream& out) const =0; //allowing subclasses to overload the operator<< of the base class
};

// subclasses of Order
class Deploy : public Order {
 public:
  Deploy(Territory* target, Player* owner, int numOfArmies);
  void execute();
  bool validate();
  int GetNumArmies();
  Player* GetOwner();
  Territory* GetTarget();
  string stringToLog();

 private:
 void Print(std::ostream& out) const;
  Territory* Target;
  Player* Owner;
  int NumOfArmies;
};

class Advance : public Order {
 public:
  Advance(Territory* target, Territory* source, Player* owner, int numOfArmies);
  void execute();
  bool validate();
  int GetNumArmies();
  Player* GetOwner();
  Territory* GetTarget();
  Territory* GetSource();
  string stringToLog();

 private:
 void Print(std::ostream& out) const;
  Territory* Source;
  Territory* Target;
  Player* Owner;
  int NumOfArmies;
};

class Bomb : public Order {
 public:
  Bomb(Territory* target, Player* owner);
  void execute();
  bool validate();
  string stringToLog();

 private:
 void Print(std::ostream& out) const;
  Player* Owner;
  Territory* Target;
};

class Blockade : public Order {
 public:
  Blockade(Territory* target, Player* owner, Player* neutral);
  void execute();
  bool validate();
  string stringToLog();

 private:
 void Print(std::ostream& out) const;
  Territory* Target;
  Player* Owner;
  Player* NeutralPlayer = NULL;
};

class Airlift : public Order {
 public:
  Airlift(Territory* target, Territory* source, Player* owner, int numOfArmies);
  void execute();
  bool validate();
  string stringToLog();

 private:
 void Print(std::ostream& out) const;
  Territory* Source;
  Territory* Target;
  int NumOfArmies;
  Player* Owner;
};

class Negotiate : public Order {
 public:
  Negotiate(Territory* target, Player* owner);
  void execute();
  bool validate();
  string stringToLog();

 private:
 void Print(std::ostream& out) const;
  Territory* Target;
  Player* Owner;
};

class OrdersList : public Subject, public ILoggable {
 public:
  OrdersList();
  OrdersList(const OrdersList& ordersList);
  //~OrdersList();
  OrdersList& operator=(const OrdersList& ordersList);
  void move(int initial, int final);
  void remove(int index);
  void add(Order* order);
  friend std::ostream& operator<<(std::ostream& o, const OrdersList& oL);
  void executeOrders();
  string stringToLog();

 private:
  std::vector<Order*> ListOfOrders;
};

#endif