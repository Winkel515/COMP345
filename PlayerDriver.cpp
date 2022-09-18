#include <iostream>

class PlayerTests {
 public:
  static int testOne() { std::cout << "Running test one\n"; }
};

int testPlayers() {
  std::cout << "Running Player tests\n";
  PlayerTests::testOne();
  std::cout << "Done running Player tests\n";
  return 0;
}