#include "PlayerDriver.h"

#include <iostream>
#include <list>

#include "Player.h"

using namespace std;

namespace PlayerTests {

// Testing toDefend()
int test1() {
  cout << "Starting PlayerTests.test1(): testing toDefend()\n";

  Player player1;
  list<Fake::Territory*> territories = player1.toDefend();

  cout << "test1() has ran successfully\n";
  return 0;
}

// Testing toAttack()
int test2() {
  cout << "Starting PlayerTests.test2(): testing toAttack()\n";

  Player player1;
  list<Fake::Territory*> territories = player1.toAttack();

  cout << "test2() has ran succesfully\n";
  return 0;
}

// Testing issueOrder()
int test3() {
  cout << "Starting PlayerTests.test3(): testing issueOrder()\n";

  Player player1;
  cout << "add 3 orders\n";
  player1.issueOrder();
  player1.issueOrder();
  player1.issueOrder();
  player1.testListOrder();
  cout << "add 2 more orders\n";
  player1.issueOrder();
  player1.issueOrder();
  player1.testListOrder();
  cout << "test3() has ran succesfully\n";
  return 0;
}
};  // namespace PlayerTests

// Test Player class
int testPlayers() {
  cout << "Running Player tests\n";
  PlayerTests::test1();
  PlayerTests::test2();
  PlayerTests::test3();
  cout << "Done running Player tests\n";
  return 0;
}

// For Debugging Purposes
// int main() { testPlayers(); };
