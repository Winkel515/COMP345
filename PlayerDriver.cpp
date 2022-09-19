#include <iostream>
#include <list>

#include "Player.cpp"

using namespace std;

namespace PlayerTests {
int test1() {
  cout << "Starting test1(): testing toDefend()\n";

  Player player1;
  list<Fake::Territory*> territories = player1.toDefend();

  cout << "test1() has ran successfully\n";
  return 0;
}

int test2() {
  cout << "Starting test2(): testing toAttack()\n";

  Player player1;
  list<Fake::Territory*> territories = player1.toAttack();

  cout << "test2() has ran succesfully\n";
  return 0;
}

int test3() {
  cout << "Starting test3(): testing issueOrder()\n";

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
