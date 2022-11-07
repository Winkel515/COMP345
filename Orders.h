#ifndef Orders_H
#define Orders_H
#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include "Player.h"

//abstract class
class Order {
 public:
  Order();
  Order(const Order &o);
  Order &operator=(const Order &copy);
  ~Order();
  friend std::ostream &operator<<(std::ostream &output, const Order &o);
  virtual bool validate() = 0; //pure virtual
  virtual void execute() = 0; //pure virtual
  virtual std::string GetType() = 0; //pure virtual

 private:
  std::string orderEffect;
};

//subclasses of Order
class Deploy : public Order{
  public:
    Deploy(Territory* target, Player* owner, int numOfArmies);
    void execute();
    bool validate();
    int GetNumArmies();
    Player* GetOwner();
    Territory* GetTarget();
    friend std::ostream &operator<<(std::ostream &output, const Deploy &o);

  private:
    Territory* Target;
    Player* Owner;
    int NumOfArmies;
};

class Advance : public Order{
  public:
    Advance(Territory* target, Territory* source, Player* owner, int numOfArmies);
    void execute();
    bool validate();
    int GetNumArmies();
    Player* GetOwner();
    Territory* GetTarget();
    Territory* GetSource();
    friend std::ostream &operator<<(std::ostream &output, const Advance &o);

  private:
    Territory* Source;
    Territory* Target;
    Player* Owner;
    int NumOfArmies;

};

class Bomb : public Order {
  public:
  void execute();
  bool validate();
  friend std::ostream &operator<<(std::ostream &output, const Bomb &o);
};

class Blockade : public Order{
  public:
  void execute();
  bool validate();
  friend std::ostream &operator<<(std::ostream &output, const Blockade &o);
};

class Airlift : public Order{
  public:
  void execute();
  bool validate();
  friend std::ostream &operator<<(std::ostream &output, const Airlift &o);
};

class Negotiate : public Order{
  public:
  void execute();
  bool validate();
  friend std::ostream &operator<<(std::ostream &output, const Negotiate &o);
};

class OrdersList {
 public:
  OrdersList();
  OrdersList(const OrdersList &ordersList);
  ~OrdersList();
  OrdersList &operator=(const OrdersList &ordersList);
  void move(int initial, int final);
  void remove(int index);
  void add(Order *order);
  friend std::ostream &operator<<(std::ostream &o, const OrdersList &oL);
  void executeOrders();

 private:
  std::vector<Order *> ListOfOrders;
};

#endif